#pragma once
#include "lynq/cloud/CloudModels.h"
#include <cstdint>
namespace lynq::hub {
class ICloudTransport { public: virtual ~ICloudTransport()=default; virtual bool connected() const=0; virtual bool receive(cloud::RemoteCommand&)=0; virtual void sendAcknowledgement(const cloud::CommandAcknowledgement&)=0; };
class IRemoteDispatch { public: virtual ~IRemoteDispatch()=default; virtual bool dispatch(const cloud::RemoteCommand&,std::string& detail)=0; };
class CloudSyncService { public: CloudSyncService(ICloudTransport&t,IRemoteDispatch&d):transport_(t),dispatch_(d){} void poll(std::uint64_t now); private:ICloudTransport&transport_;IRemoteDispatch&dispatch_;};
}
