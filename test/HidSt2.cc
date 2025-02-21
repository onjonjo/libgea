/* -*-	Mode:C++; c-basic-offset:4; tab-width:8; indent-tabs-mode:t -*- */

#include <gea/Handle.h>
#include <gea/Time.h>
#include <gea/API.h>
#include <gea/Blocker.h>
#include <gea/UdpHandle.h>

using namespace std;

static const int PORT = 4407;


class HidSt {
public:
    
    gea::AbsTime t0;

    /* ::Node *node; */
    gea::Blocker blocker;
    gea::UdpHandle *udp;

    int msgnr;
    double freq;

    HidSt(double freq);
    static void broadcast_event(gea::Handle *h, gea::AbsTime t, void *data);
    static void write_ready_event(gea::Handle *h, gea::AbsTime t, void *data);
};

HidSt::HidSt(double freq) :
    t0(gea::AbsTime::now()),
    msgnr(0), 
    freq(freq)
{
    this->udp = new gea::UdpHandle( gea::UdpHandle::Write,
				    gea::UdpAddress( gea::UdpAddress::IPADDR_BROADCAST,
						     PORT /*port*/ ));

    GEA.waitFor(&blocker,
		gea::AbsTime::now() + 0.01,
		HidSt::broadcast_event,
		this);
}


void HidSt::broadcast_event(gea::Handle *h, gea::AbsTime t, void *data) {
    HidSt *self = reinterpret_cast<class HidSt *>(data);
    GEA.waitFor( &( self->blocker ),
		 t + gea::Duration(self->freq),
		 HidSt::broadcast_event,
		 data);

    GEA.waitFor( self->udp,
		 t + gea::Duration(0.09),
		 HidSt::write_ready_event,
		 data);
}

void HidSt::write_ready_event(gea::Handle *h, gea::AbsTime t, void *data) {

    //  cout << ( t - gea::AbsTime::t0()) << ": trying to send  " <<  endl;


    HidSt *self = reinterpret_cast<class HidSt *>(data);

    self->msgnr += 2;

    char buf[1024];

    *((int *)buf) = self->msgnr;

    if ( self->udp->write(buf,1000) == -1)
	GEA.dbg() << "cannot send" << endl;;

}

extern "C"
int gea_main(int argc, const char * const *argv) {
    
    double freq = 0.1;
    
    if (argc > 2)
	freq = atof(argv[1]);

    new HidSt(freq);

    return 0;
}
