/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Mouse3DTask.hpp"
#include <controldev/ConnexionHID.hpp>
#include <rtt/extras/FileDescriptorActivity.hpp>

using namespace controldev;

Mouse3DTask::Mouse3DTask(std::string const& name)
    : Mouse3DTaskBase(name)
{
    interface = new ConnexionHID();
    std::vector<double> v= _axisScale.get();
    v.resize(6);
    for(int i=0;i<6;i++){
        v[i] = interface->axisScalinig((ConnexionHID::Mapping)i); 
    }
    _axisScale.set(v);

}

Mouse3DTask::Mouse3DTask(std::string const& name, RTT::ExecutionEngine* engine)
    : Mouse3DTaskBase(name, engine)
{
    interface = new ConnexionHID();
    std::vector<double> v= _axisScale.get();
    v.resize(6);
    for(int i=0;i<6;i++){
        v[i] = interface->axisScalinig((ConnexionHID::Mapping)i); 
    }
    _axisScale.set(v);

}

Mouse3DTask::~Mouse3DTask()
{
    delete interface;
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See Mouse3DTask.hpp for more detailed
// documentation about them.
bool Mouse3DTask::configureHook()
{
    if (! controldev::GenericTask::configureHook())
        return false;


    if (!interface->init())
    {
        std::cerr << "Warning: Unable to open 3D Mousedevice" << std::endl;
	return false;
    }

    std::vector<double> v= _axisScale.get();
    if(v.size() != 6){
        std::cerr << "Axis scale has wrong dimension" << std::endl;
        return false;
    }
    for(int i=0;i<6;i++){
        interface->axisScalinig((ConnexionHID::Mapping)i) = v[i]; 
    }
    return true;
    
}

int Mouse3DTask::getFileDescriptor()
{
    return interface->getFileDescriptor();
}

bool Mouse3DTask::updateRawCommand(RawCommand& rcmd)
{
    rcmd.deviceIdentifier= "3DMouse";
   
    rcmd.axisValue.resize(6);
   
    connexionValues values;
    connexionValues rawValues;
    interface->getValue(values,rawValues);

    rcmd.axisValue[0] = values.tx;
    rcmd.axisValue[1] = values.ty;
    rcmd.axisValue[2] = values.tz;
    rcmd.axisValue[3] = values.rx;
    rcmd.axisValue[4] = values.ry;
    rcmd.axisValue[5] = values.rz;
    rcmd.buttonValue.push_back(values.button1);
    rcmd.buttonValue.push_back(values.button2);
    
    return true;
}


void Mouse3DTask::stopHook()
{
    
    controldev::GenericTask::stopHook();
}



void Mouse3DTask::cleanupHook()
{
    
    controldev::GenericTask::cleanupHook();
}

