#include <iostream>
#include <string>

#include <ccpp_dds_dcps.h>

#include <idl/ccpp_PID.h>

#include "reader.h"

extern int shutdown_flag;

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

                DDS::ReturnCode_t retval;
                DDS::SampleInfoSeq infoseq;
                PresenceSeq pseq;
                retval =preader->take(pseq,
                                      infoseq,
                                      DDS::LENGTH_UNLIMITED,
                                      DDS::NOT_READ_SAMPLE_STATE,
                                      DDS::ANY_INSTANCE_STATE,
                                      DDS::ALIVE_INSTANCE_STATE);
                if( DDS::RETCODE_OK != retval ){
                    // This used to be an assert to fail. But now I'm thinking
                    // this could just be a timing issue that we need to handle normally.
                    return;
                }

                DDS::InstanceHandle_t pubhandle;
                // If I turn this in to a _var the get_matched_publication_data never returns
                DDS::PublicationBuiltinTopicData pubdata;
                if( pseq.length() > 0){
                    std::cout << "On data available" << std::endl;
                    pubhandle = infoseq[0].publication_handle;
                    assert( pubhandle != DDS::HANDLE_NIL );
                    // Do we want the narrowed reader?
                    // std::cout << "Getting the pubdata" << std::endl;
                    retval = reader->get_matched_publication_data(pubdata,pubhandle);
                    // std::cout << "Done getting pubdata" << std::endl;

                    DDS::UserDataQosPolicy user_data = pubdata.user_data;
                    // This string constructor uses the length -- so no \0 necessary?
                    assert(user_data.value.length() > 0);
                    std::string tempstr = std::string(reinterpret_cast<const char*>(user_data.value.get_buffer()),user_data.value.length());
                    std::cout << tempstr << std::endl;

                    assert( DDS::RETCODE_OK == retval );
                }
                //shutdown_flag = 1;
            }
            void PresenceReaderListener::on_subscription_matched(DDS::DataReader_ptr reader, const DDS::SubscriptionMatchedStatus& status){
                std::cout << "On subscribtion matched" << std::endl;
            }
            void PresenceReaderListener::on_sample_lost(DDS::DataReader_ptr reader, const DDS::SampleLostStatus& status){
                std::cout << "On sample last" << std::endl;
            }
}
