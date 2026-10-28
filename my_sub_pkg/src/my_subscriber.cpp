#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include <chrono>  
#include <memory>  
class My_Subscriber:public rclcpp::Node{
public:
My_Subscriber() : Node("my_subscriber_node"){
  subscriber_=  this->create_subscription<geometry_msgs::msg::PoseStamped>("my_topic",10,
   std::bind(&My_Subscriber::topic_callback, this, std::placeholders::_1)); 
}
private:
 void topic_callback(const geometry_msgs::msg::PoseStamped::SharedPtr msg) const {
        RCLCPP_INFO(this->get_logger(), "我收到了: x='%f'", msg->pose.position.x);
        RCLCPP_INFO(this->get_logger(), "y='%f'", msg->pose.position.y);
    }
     rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr subscriber_;
};
int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<My_Subscriber>());
    rclcpp::shutdown();
    return 0;
}