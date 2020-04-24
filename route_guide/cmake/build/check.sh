echo $1
aws ec2 start-instances --instance-ids $1
sleep 30
IP=$(aws ec2 describe-instances --filters Name=instance-id,Values=$1 | jq ".Reservations[0].Instances[0].NetworkInterfaces[0].Association.PublicIp" | sed s/\"//g)
ssh -i "csce6781.pem" -o StrictHostKeyChecking=no ec2-user@${IP} "exit"
scp -i "csce6781.pem" client.sh ec2-user@${IP}:/home/ec2-user/grpc/examples/cpp/route_guide/cmake/build/client.sh
ssh -i "csce6781.pem" -o StrictHostKeyChecking=no ec2-user@${IP} "nohup bash -x /home/ec2-user/grpc/examples/cpp/route_guide/cmake/build/client.sh $2  0<&- &>log.file & exit"
exit
