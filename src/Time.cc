#include <gea/config.h>

#include <sys/time.h>
#include <time.h>

#ifdef HAVE_WINDOWS_H
#include <windows.h>
#endif // HAVE_WINDOWS_H

#include <gea/Time.h>
#include <gea/posix/PosixApiIface.h>


void gea::PosixApiIface::getCurrentTime(gea::AbsTime *p_now) {
    
    long long nsec;
    
#if HAVE_WINDOWS_H
    // p_now->v =  * ( FixNum::offset / 1000L );
    nsec = (long long )GetTickCount() * 1000000LL;
#else
    struct timeval tv;
    ::gettimeofday(&tv,0);
    //    p_now->v = AbsTime::StoreType(tv.tv_sec) * FixNum::offset;
    // p_now->v += AbsTime::StoreType(tv.tv_usec) * ( FixNum::offset / 1000000L );
    nsec = ( (long long)tv.tv_sec * 1000000000LL) + ((long long)tv.tv_usec * 1000LL);
#endif // HAVE_WINDOWS_H
    
    p_now->setNanoSecs(nsec);
}





/* This stuff is for emacs
 * Local variables:
 * mode:c++
 * c-basic-offset: 4
 * End:
 */
