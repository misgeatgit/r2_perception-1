#include "ros/ros.h"
#include "Fusion.h"

class FusionServer{
    private:
        std::vector<FusionModule*> _modules;
        ros::Rate _loop_rate;
        ros::NodeHandle server_node;

        ros::Publisher load_module_pub;
        ros::Publisher unload_module_pub;
        ros::Publisher list_module_pub;

    public:
        FusionServer(unsigned int loop_rate = 10);
        ~FusionServer();

        // Dynamical loader for ROS fusion nodes
        bool load(r2_perception::loadModule& req);
        void unload(r2_perception::unloadModule& req);
        void listmodule(r2_perception::listModule& res);
};

FusionServer::FusionServer(unsigned int loop_rate/*=10*/){
    // Create ROS node
    server_node.advertise_service("loadmodule", load);
    server_node.advertise_service("unloadmodule", unload);
    server_node.advertise_service("listmodule", listmodule);
}

~FusionServer::FusionServer(){

}

// Publish topics periodically.
void FusionServer::run(void){
    while (ros::ok()){
        for(const FusionModule* module : _modules){
            module->publish();
        } 
        ros::spinOnce();
        loop_rate.sleep();
    }
}

bool FusionServer::load(r2_perception::loadModule& req){
// req.module_path;
}

void FusionServer::unload(r2_perception::unloadModule& req){
// req.module_id;
}

void FusionServer::listmodule(r2_perception::listModule& res){
// res.modules;
}
