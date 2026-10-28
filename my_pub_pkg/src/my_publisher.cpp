#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include <chrono>  
#include <memory>  

class MyPublisher : public rclcpp::Node {
public:
    MyPublisher() : Node("my_publisher_node") {
        publisher_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("my_topic", 10);
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(500),
            std::bind(&MyPublisher::timer_callback, this));
    }

private:
    void timer_callback() {
        auto message = geometry_msgs::msg::PoseStamped();
        message.pose.position.x=1.0;
        message.pose.position.y=2.0;
        RCLCPP_INFO(this->get_logger(), "Publishing:x= '%f'", message.pose.position.x);
        RCLCPP_INFO(this->get_logger(), "y='%f'", message.pose.position.y);
        publisher_->publish(message);
    }

    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MyPublisher>());
    rclcpp::shutdown();
    return 0;
}