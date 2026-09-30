#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/relative_humidity.hpp"
#include "sensor_msgs/msg/temperature.hpp"

class MonitorNode : public rclcpp::Node
{
public:
  MonitorNode() : Node("monitor_node")
  {
    temp_sub_ = create_subscription<sensor_msgs::msg::Temperature>(
      "temperature",
      10,
      std::bind(&MonitorNode::check_temperature, this, std::placeholders::_1));

    humidity_sub_ = create_subscription<sensor_msgs::msg::RelativeHumidity>(
      "humidity",
      10,
      std::bind(&MonitorNode::check_humidity, this, std::placeholders::_1));

    RCLCPP_INFO(get_logger(), "Monitor node elindult, várakozás...");
  }

private:
  void check_temperature(const sensor_msgs::msg::Temperature::SharedPtr msg)
  {
    if (msg->temperature > 35.0) {
      RCLCPP_WARN(
        get_logger(),
        "High temperature: %.0f C",
        msg->temperature);
    }
  }

  void check_humidity(const sensor_msgs::msg::RelativeHumidity::SharedPtr msg)
  {
    double humidity = msg->relative_humidity * 100.0;

    if (humidity > 75.0) {
      RCLCPP_WARN(
        get_logger(),
        "High humidity: %.0f %%",
        humidity);
    }
  }

  rclcpp::Subscription<sensor_msgs::msg::Temperature>::SharedPtr temp_sub_;
  rclcpp::Subscription<sensor_msgs::msg::RelativeHumidity>::SharedPtr humidity_sub_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MonitorNode>());
  rclcpp::shutdown();
  return 0;
}