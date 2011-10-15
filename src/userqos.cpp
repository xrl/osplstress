#include <stdlib.h>
#include <assert.h>

#include <ccpp_dds_dcps.h>

int main(int argc, char** args){
  // DomainParticipantFactory_var dpf = DDS::DomainParticipantFactory::get_instance();
  DDS::DomainParticipantFactory_var dpf = DDS::DomainParticipantFactory::get_instance();
  assert( NULL != dpf._retn());
  assert( NULL != &dpf );
  //            DomainParticipant_var participant;
  DDS::DomainParticipant_var participant = dpf->create_participant(NULL,
                                                                   PARTICIPANT_QOS_DEFAULT,
                                                                   NULL,
                                                                   DDS::STATUS_MASK_NONE);
  assert( NULL == participant );
  assert( NULL != participant._retn() ); 
  
//  participant._retn()->delete_participant();
  return 0;
}
