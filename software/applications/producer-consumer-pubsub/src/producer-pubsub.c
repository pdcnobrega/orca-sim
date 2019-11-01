#include <hellfire.h>
#include <noc.h>

#include "producer-consumer-pubsub.h"
#include "../../orca-pubsub/include/pubsub-shared.h"
#include "../../orca-pubsub/include/pubsub-publisher.h"

#define PRODUCE_LENGTH 32

#define BROKER_ADDR 3

#define PUBLISHER_PORT 2005

void producer_pubsub(void){
	
	int8_t buf[PRODUCE_LENGTH];

	// "opens" the comm
	if(hf_comm_create(hf_selfid(), PUBLISHER_PORT, 0))
		panic(0xff);

	//delay necessary for the kernel to create the comm
	delay_ms(60);
	
	//broker info (design time config.)
	pubsub_node_info_t brokerinfo = {
		.address = BROKER_ADDR,
		.port    = PS_BROKER_DEFAULT_PORT
	};
	
	//this node
	pubsub_node_info_t pubinfo = {
		.address = hf_selfid(),
		.port    = PUBLISHER_PORT //TODO: get this automatically?
	}; 

	//advertise to TOPIC_01, advertiser resides in port 2000
	pubsub_advertise(pubinfo, brokerinfo, TOPIC_01);
	pubsub_unadvertise(pubinfo, brokerinfo, TOPIC_01);
	
	pubsub_advertise(pubinfo, brokerinfo, TOPIC_01);
	pubsub_unadvertise(pubinfo, brokerinfo, TOPIC_01);
	
	pubsub_advertise(pubinfo, brokerinfo, TOPIC_01);

	//hf_send(1, 5, buf, sizeof(buf), 1000);

	//keep producing messages  
	while(1){

		//generate a bunch of values
		for (int i = 0; i < PRODUCE_LENGTH; i++)
			buf[i] = i;
		
		//printf("s -> 1\n");
		//hf_send(1, 5, buf, sizeof(buf), 1000);
		
		//publishes to the topic
		pubsub_publish(TOPIC_01, buf, sizeof(buf));
	}
	
	
}
