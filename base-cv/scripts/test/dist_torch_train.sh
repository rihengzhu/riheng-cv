
tag=$1
time=`date "+%y%m%d"`
name ='1111'$time'-'$tag
saved_prefix=''$name
saved_prefix=`realpath`$saved_prefix

if [! -d '$saved_prefix'];then
    echo 'create dir:'$saved_prefix
    mkdir -p $saved_prefix
    chmod 777 -R $saved_prefix
    cp -r ../../scripts $saved_prefix
    cp -r ../../train_cv $saved_prefix
fi


GPUS=0
PORT=${PORT:-29697}
pytorch -m torch.distributed.launch --npro_per_nodes=$GPUS --master_port=$PORT\
$(dirname "$0")/torch_train.py config_name --launcher pytorch --gpu-dis 0 1 2 3 --word-dir ${saved_prefix}