from multiprocessing import Pool
import mmcv
import numpy as np
from mmcv.utils import print_log
from terminaltables import AsciiTable

from mmdet.core.evaluation.bbox_overlaps import bbox_overlaps
from mmdet.core.evaluation.class_names import get_classes
from mmdet.core.evaluation.mean_ap import average_precision
from ..utils.eval_map import iou, save_fp_fn
import cv2

cv2.setNumThreads(0)





def print_map_summary(mean_ap,
                      results,
                      dataset=None,
                      scale_ranges=None,
                      logger=None):
    """Print mAP and results of each class.

    A table will be printed to show the gts/dets/recall/AP of each class and
    the mAP.

    Args:
        mean_ap (float): Calculated from `eval_map()`.
        results (list[dict]): Calculated from `eval_map()`.
        dataset (list[str] | str | None): Dataset name or dataset classes.
        scale_ranges (list[tuple] | None): Range of scales to be evaluated.
        logger (logging.Logger | str | None): The way to print the mAP
            summary. See `mmcv.utils.print_log()` for details. Default: None.
    """

    if logger == 'silent':
        return

    if isinstance(results[0]['ap'], np.ndarray):
        num_scales = len(results[0]['ap'])
    else:
        num_scales = 1

    if scale_ranges is not None:
        assert len(scale_ranges) == num_scales

    num_classes = len(results)
    num_cls = int(len(results[0]['cls_res'])**0.5)

    recalls = np.zeros((num_scales, num_classes), dtype=np.float32)
    cls_res = np.zeros((num_cls**2, num_scales, num_classes),dtype=np.float32)
    scores = np.zeros((num_scales, num_classes), dtype=np.float32)
    m_iou = np.zeros((num_scales, num_classes), dtype=np.float32)
    w_rela = np.zeros((num_scales, num_classes), dtype=np.float32)
    precisions = np.zeros((num_scales, num_classes), dtype=np.float32)
    aps = np.zeros((num_scales, num_classes), dtype=np.float32)
    num_gts = np.zeros((num_scales, num_classes), dtype=int)
    for i, cls_result in enumerate(results):
        indexes=np.array(cls_result['index'])
        if cls_result['recall'].size > 0:
            for j, index in enumerate(indexes):
                scores[j,i] = np.array(cls_result['scores'],ndim=1)[index]
                recalls[j, i] = np.array(cls_result['recall'], ndmin=2)[j,index]
                precisions[j, i] = np.array(cls_result['precision'], ndmin=2)[j, index]
                m_iou[j, i] = np.array(cls_result['mean_ious'], ndmin=2)[j, index]
                w_rela[j, i] = np.array(cls_result['relative_w'], ndmin=2)[j, index]
                cls_res[j, i] = np.array(cls_result['cls_res'], ndmin=3)[j, index]
        aps[:, i] = cls_result['ap']
        num_gts[:, i] = cls_result['num_gts']

    if dataset is None:
        label_names = [str(i) for i in range(num_classes)]
    elif mmcv.is_str(dataset):
        label_names = get_classes(dataset)
    else:
        label_names = dataset

    if not isinstance(mean_ap, list):
        mean_ap = [mean_ap]

    header = ['distnace', 'gts',  'recall','prec','score','m_iou','dw/gw', 'ap']
    for i in range(num_scales):
        if distance is not None:
            print_log(f'Scale range {scale_ranges[i]}', logger=logger)
        table_data = [header]
        for j in range(num_classes):
            row_data = [
                label_names[j], num_gts[i, j], results[j]['num_dets'],
                f'{recalls[i, j]:.3f}', f'{aps[i, j]:.3f}'
            ]
            table_data.append(row_data)
        table_data.append(['mAP', '', '', '', f'{mean_ap[i]:.3f}'])
        table = AsciiTable(table_data)
        table.inner_footing_row_border = True
        print_log('\n' + table.table, logger=logger)


def tpfpfn_default(det_bboxes,
                   gt_bboxes,
                   gt_bboxes_ignore=None,
                   iou_thr=0.5,
                   area_ranges=None,
                   scale_type='area',
                   num_classes=1):
    gt_ignore_inds = np.concatenate(
        (np.zeros(gt_bboxes.shape[0],dtype=np.bool),
         np.ones(gt_bboxes_ignore.shape[0],dtype=np.bool)))
    gt_bboxes = np.vstack((gt_bboxes,gt_bboxes_ignore))
    num_dets = det_bboxes.shape[0]
    num_gts = gt_bboxes.shape[0]
    if area_ranges is None:
        area_ranges = [(None,None)]
    num_scales = len(area_ranges)

    tp = np.zeros((num_scales, num_dets),dtype=np.float32)
    fp = np.zeros((num_scales, num_dets),dtype=np.float32)
    tp_ious = np.zeros((num_scales, num_dets),dtype=np.float32)
    w_relative = np.zeros((num_scales, num_dets), dtype=np.float32)

    if gt_bboxes.shape[0] ==0:
        if area_ranges == [(None, None)]:
            fp[...] = 1
        else:
            if scale_type == 'area':
                det_areas = (det_bboxes[:, 2] - det_bboxes[:, 0]) * (det_bboxes[:, 3] - det_bboxes[:, 1])
                for i,(min_area,max_area) in enumerate(area_ranges):
                    fp[i,(det_areas>=min_area)&(det_areas<max_area)] = 1
            elif scale_type =='height':
                det_h = (det_bboxes[:, 3] - det_bboxes[:, 1])
                for i,(min_area,max_area) in enumerate(area_ranges):
                    fp[i,(det_h>=min_area)&(det_h<max_area)] = 1
            elif scale_type =='width':
                det_w = (det_bboxes[:, 2] - det_bboxes[:, 0])
                for i,(min_area,max_area) in enumerate(area_ranges):
                    fp[i,(det_w>=min_area)&(det_w<max_area)] = 1
            else:
                  assert f'{scale_type} is not supported'
        return tp, fp, tp_ious, w_relative, np.zeros(num_gts,dtype=bool),np.zeros(num_dets),np.ones(
            num_dets)*-1, np.zeros(num_gts),np.zeros(num_gts)
    ious = bbox_overlaps(det_bboxes, gt_bboxes)
    ious_max = ious.max(axis=1)
    ious_argmax = ious.argmax(axis=1)
    if len(det_bboxes) ==0:
        sort_inds = []
    else:
        sort_inds = np.argsort(-det_bboxes[:, -2])
    for k,(min_area, max_area) in enumerate(area_ranges):
        gt_covered = np.zeros(num_gts,dtype=bool)
        if min_area is None:
            gt_area_ignore = np.zeros_like(gt_ignore_inds, dtype=bool)
        else:
            if scale_type == 'area':
                gt_areas = (gt_bboxes[:, 2] - gt_bboxes[:, 0]) * (gt_bboxes[:, 3] - gt_bboxes[:, 1])
                gt_area_ignore =(gt_areas<min_area)|(gt_areas>=max_area)
            elif scale_type == 'height':
                gt_h = (gt_bboxes[:, 3] - gt_bboxes[:, 1])
                gt_area_ignore =(gt_h<min_area)|(gt_h>=max_area)
            elif scale_type == 'width':
                gt_w = (gt_bboxes[:, 2] - gt_bboxes[:, 0])
                gt_area_ignore =(gt_w<min_area)|(gt_w>=max_area)
            else:
                assert f'{scale_type} is not supported'
        for i in sort_inds:
            if ious_max[i]>= iou_thr:
                matched_gt = ious_argmax[i]
                if not (gt_ignore_inds[matched_gt] or gt_area_ignore[matched_gt]):
                    if not gt_covered[matched_gt]:
                        gt_covered[matched_gt]=True
                        gt_label = gt_bboxes[matched_gt,-1]
                        det_label = det_bboxes[i,-1]
                        tp[k,i] = num_classes * gt_label +det_label +1
                        tp_ious[k,i] = ious_max[i]
                        det_w = gt_bboxes[matched_gt,2] - gt_bboxes[matched_gt,0]
                        w_relative[k,i] = abs(det_w - gt_w)/gt_w

            elif min_area is None:
                fp[k, i] = 1
            else:
                bbox = det_bboxes[i, :4]
                area = (bbox[2] - bbox[0] + extra_length) * (
                    bbox[3] - bbox[1] + extra_length)
                if area >= min_area and area < max_area:
                    fp[k, i] = 1
    return tp, fp, tp_ious, w_relative, gt_covered, ious_max, ious_argmax, gt_bboxes, gt_ignore_inds

def eval_det(det_results,
             img_path,
             annotations,
             ann_info,
             scale_ranges=None,
             iou_thr=0.5,
             save_fpfn=False,
             save_dir=None,
             show_score=0.1,
             dataset=None,
             logger=None,
             nproc=4,
             scale_type='area'):
    assert len(det_results) == len(annotations)
    num_imgs = len(det_results)
    num_scales = len(scale_ranges)
    num_classes = len(det_results[0])
    if scale_type == 'area':
        area_ranges = ([(rg[0]**2,rg[1]**2) for rg in scale_ranges]
                        if scale_ranges is not None else None)
    else:
        area_ranges = ([(rg[0],rg[1]) for rg in scale_ranges]
                        if scale_ranges is not None else None)
    eval_results = []
    pool = Pool(nproc)
    cls_dets,cls_gts,cls_gts_ignore = get_results_total(det_results,annotations)
    tpfp_func = tpfpfn_default
    tpfp = pool.startmap(
                tpfp_func,
                zip(cls_dets,cls_gts,cls_gts_ignore,
                    [iou_thr for _ in range(num_imgs)],
                    [area_ranges for _ in range(num_imgs)],
                    [scale_type for _ in range(num_imgs)],
                    [num_classes for _ in range(num_imgs)]))
    tp,fp,tp_ious,rela_w,gt_covered,ious_max,ious_argmax,all_gt_bboxes,gt_ignore_inds = tuple(
        zip(*tpfp))
    num_gts = np.zeros(num_scales, dtype=np.int)
