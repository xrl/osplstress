#include <iostream>

#include <ccpp_dds_dcps.h>

#include <idl/ccpp_PID.h>

#include "reader.h"

namespace PID{
            void PresenceReaderListener::on_requested_deadline_missed(DDS::DataReader_ptr reader, const DDS::RequestedDeadlineMissedStatus& status){
                std::cout << "On requested deadline missed" << std::endl;
            }
            void PresenceReaderListener::on_requested_incompatible_qos(DDS::DataReader_ptr reader, const DDS::RequestedIncompatibleQosStatus& status){
                std::cout << "On requested incompatible qos" << std::endl;
            }
            void PresenceReaderListener::on_sample_rejected(DDS::DataReader_ptr reader, const DDS::SampleRejectedStatus& status){
                std::cout << "On sample reject" << std::endl;
            }
            void PresenceReaderListener::on_liveliness_changed (DDS::DataReader_ptr reader, const DDS::LivelinessChangedStatus& status){
                std::cout << "On liveliness changed" << std::endl;
            }
            void PresenceReaderListener::on_data_available(DDS::DataReader_ptr reader){
                PresenceDataReader_ptr preader = PresenceDataReader::_narrow(reader);
                assert(preader != NULL);

                DDS::SampleInfoSeq infoseq;
                PresenceSeq pseq;
                preader->take(pseq,
                              infoseq,
                              DDS::LENGTH_UNLIMITED,
                              DDS::NOT_READ_SAMPLE_STATE,
                              DDS::ANY_INSTANCE_STATE,
                              DDS::ALIVE_INSTANCE_STATE);
                if( pseq.length() > 0){
                    std::cout << "On data available" << std::endl;
                }
            }
            void PresenceReaderListener::on_subscription_matched(DDS::DataReader_ptr reader, const DDS::SubscriptionMatchedStatus& status){
                std::cout << "On subscribtion matched" << std::endl;
            }
            void PresenceReaderListener::on_sample_lost(DDS::DataReader_ptr reader, const DDS::SampleLostStatus& status){
                std::cout << "On sample last" << std::endl;
            }
}
