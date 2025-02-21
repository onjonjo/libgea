/* -*-	Mode:C++; c-basic-offset:4; tab-width:8; indent-tabs-mode:t -*- */

#include <gea/Handle.h>
#include <gea/Time.h>
#include <gea/API.h>
#include <gea/Blocker.h>
#include <gea/UdpHandle.h>

using namespace std;

static const int PORT = 4407;

class Broadcast {
public:
    /* ::Node *node; */
    gea::Blocker blocker;
    gea::UdpHandle *udp;

    Broadcast(int argc , const char*const* argv);
    static void broadcast_event(gea::Handle *h, gea::AbsTime t, void *data);
    static void write_ready_event(gea::Handle *h, gea::AbsTime t, void *data);
};

Broadcast::Broadcast(int argc , const char*const* argv)
{
    this->udp = new gea::UdpHandle( gea::UdpHandle::Write,
				    gea::UdpAddress( gea::UdpAddress::IPADDR_BROADCAST,
						     PORT
						     ));

    GEA.waitFor(&blocker,
		gea::AbsTime::now() + 0.01,
		Broadcast::broadcast_event,
		this);
}


void Broadcast::broadcast_event(gea::Handle *h, gea::AbsTime t, void *data) {
    Broadcast *self = reinterpret_cast<class Broadcast *>(data);
    GEA.waitFor( &( self->blocker ),
		 t + gea::Duration(1),
		 Broadcast::broadcast_event,
		 data);

    GEA.waitFor( self->udp,
		 t + gea::Duration(0.09),
		 Broadcast::write_ready_event,
		 data);
}

void Broadcast::write_ready_event(gea::Handle *h, gea::AbsTime t, void *data) {

    //  cout << ( t - gea::AbsTime::t0()) << ": trying to send  " <<  endl;

    Broadcast *self = reinterpret_cast<class Broadcast *>(data);

    const char buf[1024] = "HelloWorld";
    if ( self->udp->write(buf,1000) == -1)
	GEA.dbg() << "cannot send" << endl;;
}


extern "C"
int gea_main(int argc, const char * const *argv) {

    new Broadcast(argc,argv);

    return 0;
}
