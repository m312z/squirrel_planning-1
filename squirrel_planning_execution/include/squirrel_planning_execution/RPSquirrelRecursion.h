#include <ros/ros.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <boost/foreach.hpp>
#include "mongodb_store/message_store.h"
#include "geometry_msgs/PoseStamped.h"
#include "std_srvs/Empty.h"
#include "diagnostic_msgs/KeyValue.h"

#include "rosplan_dispatch_msgs/ActionDispatch.h"
#include "rosplan_dispatch_msgs/ActionFeedback.h"

#include "rosplan_knowledge_msgs/KnowledgeItem.h"
#include "rosplan_knowledge_msgs/KnowledgeUpdateService.h"
#include "rosplan_knowledge_msgs/GetInstanceService.h"
#include "rosplan_knowledge_msgs/GetAttributeService.h"

#include "rosplan_planning_system/PlanningSystem.h"

#include "squirrel_planning_knowledge_msgs/TaskPoseService.h"

#ifndef KCL_recursion
#define KCL_recursion

/**
 * This file defines the RPSquirrelRecursion class.
 * RPSquirrelRecursion is used to execute strategic PDDL actions
 * that correspond to a tactical problem. This is done through
 * instantiating a new planning system node.
 */
namespace KCL_rosplan {

	class RPSquirrelRecursion
	{

	private:

		mongodb_store::MessageStoreProxy message_store;
		ros::ServiceClient update_knowledge_client;
		ros::Publisher action_feedback_pub;
		
		ros::ServiceClient get_instance_client;
		ros::ServiceClient get_attribute_client;
		
		// waypoint request services
		ros::ServiceClient classify_object_waypoint_client;

	public:

		/* constructor */
		RPSquirrelRecursion(ros::NodeHandle &nh);

		/* listen to and process action_dispatch topic */
		void dispatchCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg);
	};
}
#endif
