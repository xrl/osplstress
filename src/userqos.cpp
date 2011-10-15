#include <stdlib.h>
#include <assert.h>

#include <ccpp_dds_dcps.h>

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

  // Uh, don't need to register a builtin class.
  // StringSeqSupport_var stringseq_support = new StringSeqSupport();
  // retval = participant->register_type(stringseq_support->get_type_name());
  // assert( DDS::RETCODE_OK == retval );

/*(  DDS::TopicQos_var topic_qos;
  retval = participant->get_default_topic_qos(topic_qos);
  assert( DDS::RETCODE_OK == retval );
  DDS::Topic_var string_topic = participant->create_topic("system_times",
                                                          StringSeq::get_type_name(),
                                                          topic_qos,
                                                          NULL,
                                                          DDS::STATUS_MASK_NONE);
*/
  DDS::PublisherQos publisher_qos;
  retval = participant->get_default_publisher_qos(publisher_qos);
  assert( DDS::RETCODE_OK == retval );
  DDS::Publisher_var publisher = participant->create_publisher(publisher_qos,
                                                               NULL,
                                                               DDS::STATUS_MASK_NONE);
  assert( NULL != publisher._retn() );

  retval = dpf->delete_participant(participant);
  assert( DDS::RETCODE_OK == retval );
  return 0;
}
