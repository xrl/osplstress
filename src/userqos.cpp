#include <iostream>

#include <stdlib.h>
#include <assert.h>

#include <ccpp_dds_dcps.h>

#include <idl/ccpp_PID.h>

#include "userqos/reader.h"
#include "userqos/writer.h"

/**
  _var : CORBA smart pointer. It assumes control of the memory
  _ptr : You do all the work
**/

int shutdown_flag = 0;

int main(int argc, char** args){
  std::cout << "Welcome to userqos stress test" << std::endl;
  DDS::ReturnCode_t retval;
  DDS::InstanceHandle_t handle;
  
  DDS::DomainParticipantFactory_ptr dpf = DDS::DomainParticipantFactory::get_instance();
  assert( NULL != dpf);

  DDS::DomainParticipantQos participant_qos;
  retval = dpf->get_default_participant_qos(participant_qos);
  assert( DDS::RETCODE_OK == retval );
  DDS::DomainId_t domain = NULL;
  DDS::DomainParticipant_var participant = dpf->create_participant(domain,
                                                                   PARTICIPANT_QOS_DEFAULT,
                                                                   NULL,
                                                                   DDS::STATUS_MASK_NONE);
  assert( NULL != participant.in() );

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

  DDS::TopicQos topic_qos;
  retval = participant->get_default_topic_qos(topic_qos);
  assert( DDS::RETCODE_OK == retval );

  DDS::Topic_var presence_topic = participant->create_topic("presence",
                                                            pid_ts->get_type_name(),
                                                            topic_qos,
                                                            NULL,
                                                            DDS::STATUS_MASK_NONE); 
  assert( NULL != presence_topic.in() );

  /**
     Publisher code
  **/
  DDS::PublisherQos publisher_qos;
  retval = participant->get_default_publisher_qos(publisher_qos);
  assert( DDS::RETCODE_OK == retval );
  DDS::Publisher_var publisher = participant->create_publisher(publisher_qos,
                                                               NULL,
                                                               DDS::STATUS_MASK_NONE);
  assert( NULL != publisher.in() );

  /**
    PID Data Writer
  **/
  DDS::DataWriterQos dw_qos;
  retval = publisher->get_default_datawriter_qos(dw_qos);
  assert( DDS::RETCODE_OK == retval );
  const char* msg = "HI THERE COWBOY";
  dw_qos.user_data.value = DDS_DCPSUFLSeq<unsigned char, DDS::octSeq_uniq_>(msg);
  assert( strlen(msg) == dw_qos.user_data.value.length() );
  
  DDS::DataWriter_var writer = publisher->create_datawriter(presence_topic, dw_qos, NULL, DDS::STATUS_MASK_NONE); 
  assert( NULL != writer.in() );
  PID::PresenceDataWriter_var presence_writer = PID::PresenceDataWriter::_narrow(writer);
  assert( NULL != presence_writer.in() );

  /**
    Subscriber
  **/
  DDS::SubscriberQos subscriber_qos;
  retval = participant->get_default_subscriber_qos(subscriber_qos);
  assert( DDS::RETCODE_OK == retval );
  DDS::Subscriber_var subscriber = participant->create_subscriber(subscriber_qos,
                                                                  NULL,
                                                                  DDS::STATUS_MASK_NONE);
  assert( NULL != subscriber.in() );

  /**
    PID Data Reader
  **/
  DDS::DataReaderQos dr_qos;
  retval = subscriber->get_default_datareader_qos(dr_qos);
  assert( DDS::RETCODE_OK == retval );
  PID::PresenceReaderListener *p_r_listener = new PID::PresenceReaderListener();
  assert(p_r_listener != NULL);
  DDS::DataReader_ptr reader = subscriber->create_datareader(presence_topic, dr_qos, p_r_listener, DDS::DATA_AVAILABLE_STATUS);
  assert( NULL != reader );
  PID::PresenceDataReader *presence_reader = PID::PresenceDataReader::_narrow(reader);
  assert( NULL != presence_reader );

  PID::Presence temp_presence;
  temp_presence.pid = 100;
  temp_presence.hostname = "my_machine";
  handle = presence_writer->register_instance(temp_presence);
  assert( DDS::HANDLE_NIL != handle );

  std::cout << "LOOPING" << std::endl;
  while(shutdown_flag == 0){
    retval = presence_writer->write(temp_presence,handle);
    assert( DDS::RETCODE_OK == retval );
    sleep(1);
  }


  //retval = dpf->delete_participant(participant);
  //assert( DDS::RETCODE_OK == retval );
  retval = dpf->delete_contained_entities();
  assert( DDS::RETCODE_OK == retval );

  return 0;
}
