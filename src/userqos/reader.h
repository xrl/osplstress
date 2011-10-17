#include <ccpp_dds_dcps.h>
#include <idl/ccpp_PID.h>

namespace PID{
    class PresenceReaderListener : public DDS::DataReaderListener{
        public:
            void on_requested_deadline_missed(DDS::DataReader_ptr reader, const DDS::RequestedDeadlineMissedStatus& status);
            void on_requested_incompatible_qos(DDS::DataReader_ptr reader, const DDS::RequestedIncompatibleQosStatus& status);
            void on_sample_rejected(DDS::DataReader_ptr reader, const DDS::SampleRejectedStatus& status);
            void on_liveliness_changed (DDS::DataReader_ptr reader, const DDS::LivelinessChangedStatus& status);
            void on_data_available(DDS::DataReader_ptr reader);
            void on_subscription_matched(DDS::DataReader_ptr reader, const DDS::SubscriptionMatchedStatus& status);
            void on_sample_lost(DDS::DataReader_ptr reader, const DDS::SampleLostStatus& status);
    };
}
