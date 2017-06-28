#ifndef SQUIRRELPLANNINGEXECUTION_PDDLACTIONS_OBSERVE_CLASSIFIABLEONATTEMPTPDDLCOMMAND_H
#define SQUIRRELPLANNINGEXECUTION_PDDLACTIONS_OBSERVE_CLASSIFIABLEONATTEMPTPDDLCOMMAND_H

#include <ros/ros.h>
#include <rosplan_dispatch_msgs/ActionDispatch.h>

#include "mongodb_store/message_store.h"

namespace KCL_rosplan
{

/**
 * An instance of this class gets called whenever the PDDL action 'observe-classifiable_on_attempt' (or variants thereof) is
 * dispatched. It is an action that makes the robot examine all objects in the given area.
 */
class ObserveClassifiableOnAttemptPDDLAction
{
public:
	
	/**
	 * Constructor.
	 * @param node_handle An existing and initialised ros node handle.
	 */
	ObserveClassifiableOnAttemptPDDLAction(ros::NodeHandle& node_handle);
	
	/**
	 * Destructor
	 */
	~ObserveClassifiableOnAttemptPDDLAction();
	
	/**
	 * Called when this action needs to be executed.
	 * @param msg The dispatch message sent by ROSPlan.
	 * @return True if the action was successfull, false otherwise.
	 */
	void dispatchCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg);
	
private:
	
	/**
	 * Create a PDDL domain.
	 * @param object The object to be classified.
	 */
	bool createDomain(const std::string& object);
	
	static std::string g_action_name;                    // The action name as specified in PDDL files.
	
	ros::NodeHandle* node_handle_;                       // The ROS node.
	bool is_simulated_;                                  // Whether this action is to be simulated.
	
	ros::ServiceClient update_knowledge_client_;         // Service client to update the knowledge base.
	ros::ServiceClient get_instance_client_;             // Service client to get instances stored by ROSPlan.
	ros::ServiceClient get_attribute_client_;            // Service client to get attributes of instances stored by ROSPlan.
	ros::Publisher action_feedback_pub_;                 // Publisher that communicates feedback to ROSPlan.
	ros::Subscriber dispatch_sub_;                       // Subscriber to the dispatch topic of ROSPlan.
	ros::ServiceClient query_knowledge_client_;          // Service client to quiry the knowledge base.
	
	ros::ServiceClient classify_object_waypoint_client_; // waypoint request services
	
	mongodb_store::MessageStoreProxy message_store_;     // The message store proxy.
};

};

#endif
