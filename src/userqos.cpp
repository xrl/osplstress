#include <stdlib.h>
#include <assert.h>

#include <ccpp_dds_dcps.h>

#include <idl/ccpp_PID.h>

/**
  _var : CORBA smart pointer. It assumes control of the memory
  _ptr : You do all the work
**/

int main(int argc, char** args){
  DDS::ReturnCode_t retval;
  // DomainParticipantFactory_var dpf = DDS::DomainParticipantFactory::get_instance();
  DDS::DomainParticipantFactory_var dpf = DDS::DomainParticipantFactory::get_instance();
  assert( NULL != dpf._retn());
  //            DomainParticipant_var participant;
  DDS::DomainParticipant_var participant = dpf->create_participant(NULL,
                                                                   PARTICIPANT_QOS_DEFAULT,
                                                                   NULL,
                                                                   DDS::STATUS_MASK_NONE);
  assert( NULL == participant );
  assert( NULL != participant._retn() );

  /**
    Magical key definitions. If you want the idlpp to generate TypeSupport you MUST,
    I repeat, MUST, add #pragma. Why would you ever NOT want the TypeSupport? Who knows.
    OpenSplice_PreProcessor_usermanual.pdf , Section: 1.5.1 KeyDefinitions
  **/
  // Memory leak: I cannot seem to free pid_ts. Delete is blocked nor can I find _release per the docs
  PID::PresenceTypeSupport_ptr pid_ts = new PID::PresenceTypeSupport();
  assert( NULL != pid_ts );
  retval = pid_ts->register_type(participant, pid_ts->get_type_name());
  assert ( DDS::RETCODE_OK == retval );

  DDS::TopicQos_var topic_qos;
  retval = participant->get_default_topic_qos(topic_qos);
  assert( DDS::RETCODE_OK == retval );

  DDS::Topic_var presence_topic = participant->create_topic("presence",
                                                            pid_ts->get_type_name(),
                                                            topic_qos,
                                                            NULL,
                                                            DDS::STATUS_MASK_NONE); 
  assert( NULL != presence_topic._retn() );

  /**
     Publisher code
  **/
  DDS::PublisherQos publisher_qos;
  retval = participant->get_default_publisher_qos(publisher_qos);
  assert( DDS::RETCODE_OK == retval );
  DDS::Publisher_var publisher = participant->create_publisher(publisher_qos,
                                                               NULL,
                                                               DDS::STATUS_MASK_NONE);
  assert( NULL != publisher._retn() );

  /**
    PID Data Writer
  **/
  DDS::DataWriterQos dw_qos;
  publisher->get_default_datawriter_qos(dw_qos);
  const char* msg = "HI THERE COWBOY\n";
  dw_qos.user_data.value = DDS_DCPSUFLSeq<unsigned char, DDS::octSeq_uniq_>(msg);
  assert( strlen(msg) == dw_qos.user_data.value.length() );
  
  DDS::DataWriter_var writer = publisher->create_datawriter(presence_topic, dw_qos, NULL, DDS::STATUS_MASK_NONE); 
  assert( NULL != writer._retn() );
  PID::PresenceDataWriter_var presence_writer = PID::PresenceDataWriter::_narrow(writer);
  assert( NULL != presence_writer._retn() );

  /**
    Subscriber
  **/
  DDS::SubscriberQos subscriber_qos;
  retval = participant->get_default_subscriber_qos(subscriber_qos);
  assert( DDS::RETCODE_OK == retval );
  DDS::Subscriber_var subscriber = participant->create_subscriber(subscriber_qos,
                                                                  NULL,
                                                                  DDS::STATUS_MASK_NONE);
  assert( NULL != subscriber._retn() );

  /**
    PID Data Reader
  **/
  DDS::DataReaderQos dr_qos;
  retval = subscriber->get_default_datareader_qos(dr_qos);
  assert( DDS::RETCODE_OK == retval );
  DDS::DataReader_var reader = subscriber->create_datareader(presence_topic, dr_qos, NULL, DDS::STATUS_MASK_NONE);
  assert( NULL == reader._retn() );
  PID::PresenceDataReader_var presence_reader = PID::PresenceDataReader::_narrow(reader);
  assert( NULL == presence_reader._retn() );
  
  retval = dpf->delete_participant(participant);
  assert( DDS::RETCODE_OK == retval );
  return 0;
}
