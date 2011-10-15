#include <ccpp_dds_dcps.h>

int main(int argc, char** args){
  // DomainParticipantFactory_var dpf = DDS::DomainParticipantFactory::get_instance();
  DDS::DomainParticipant *participant = DDS::DomainParticipantFactory::get_instance()->create_participant(0,PARTICIPANT_QOS_DEFAULT,NULL,0);

  return 0;
}
