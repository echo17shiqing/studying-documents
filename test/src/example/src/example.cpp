#include"rclcpp/rclcpp.hpp"
#include"turtlesim/msg/pose.hpp"
#include"math.h"

class ExampleNode:public rclcpp::Node
{
private:
    //声明一个订阅者
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr sub;
    double dx=0;
    double dy=0;
    double _angle=0;
    double _angle1;

//创建一个回调函数
void callback(const turtlesim::msg::Pose::SharedPtr pose)
{
    //获得当前位置
   dx=pose->x;
   dy=pose->y;

    //计算偏角，距离
    double _angle =std::atan2(dy,dx);
    double _angle1=_angle*180/3.14;//偏角
    double _distance=std::sqrt(pow(dx,2)+pow(dy,2));//距离
    RCLCPP_INFO(this->get_logger(),"偏角:%.2f,距离:%.2f",_angle1,_distance);
    
}
public:

ExampleNode():Node("example"){
//创建一个订阅者
sub =this->create_subscription<turtlesim::msg::Pose>(
"/turtle1/pose",10,std::bind(&ExampleNode::callback,this, std::placeholders::_1));
}
};


int main(int argc,char **argv)
{
//初始化客户端
 rclcpp::init(argc,argv);
 //新建节点对象
     auto node =std::make_shared<ExampleNode>();
 //循环节点
     rclcpp::spin(node);
 //关闭客户端库
     rclcpp::shutdown();
    return 0;
}
