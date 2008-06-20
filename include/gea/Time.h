#ifndef _GEATIME_H__
#define _GEATIME_H__

#include <cassert>

#include <gea/ApiIface.h>

// we define the following to indicate that a gea timeval can be initialised from a
// double via setSeconds(double).
#define GEA_SET_TIME_FROM_DOUBLE 1

namespace gea {

    class AbsTime;

    class Duration;

    /* some forward declarations to make the friend-statements below happier */
    static Duration operator -(const AbsTime& a, const AbsTime& b);
    static AbsTime  operator +(const AbsTime& a, const Duration b);
    static AbsTime& operator +=(AbsTime& a, const Duration b);
    static AbsTime& operator -=(AbsTime& a, const Duration b);
    static AbsTime  operator -(const AbsTime& a, const Duration b);

    /** \brief Base type for fix-point number representation
     */
    class FixNum {

    public:
	/** \brief type used for storing the fix-point number */
	typedef long long StoreType;

	/** \brief the size in bytes when stored in a memory location
	 *  \see FixNum::toArray()
	 *  \see FixNum::fromArray()
	 */
	static const unsigned size = sizeof(StoreType);

    protected:

	/** \brief the variable the value is stored in
	 *
	 *  It is stored in nanoseconds.
	 */
	StoreType value;

	/** \brief defaul contructor
	 *
	 *  The default constuctor will NOT initialise the object. This is
	 *  efficient and allows us to detect uninitialised values with tools like valgrind.
	 */
	FixNum() {}


    public:
	/** \brief copy constructor
	 *
	 *  This implements the default semantics of a copy constructor.
	 */
	FixNum(const FixNum& fn) { this->value = fn.value; }

	/** \brief assignment operator with standard semantics
	 */
	FixNum& operator =(const FixNum& other) {this->value = other.value; return *this; }

	/** \brief set time value in nanoseconds
	 *
	 *  \param nsec the time value in nano seconds
	 */
	void setNanoSecs(long long nsec) {
	    value = nsec;
	}

	/** \brief set time in seconds */
	void setSeconds(double secs) {
	    value = static_cast<StoreType>(secs * 1.e9);
	}

	/** \brief get time in nanoseconds as a long long int */
	long long  getNanoSecsLL() const {
	    return value;
	}

	/** \brief get time value in nanoseconds as a double */
	double getNanoSecsD() const {
	    return static_cast<double>(value);
	}

	/** \brief get time value in seconds as a double */
	double getSecondsD() const {
	    return getNanoSecsD() * 1.e-9;
	}

	/** \brief macro for defining comparison operators */
#define bool_op(x) bool operator x (const FixNum& f) const {return this->value x f.value;}

	bool_op(==);
	bool_op(<);
	bool_op(<=);
	bool_op(>);
	bool_op(>=);
	bool_op(!=);
#undef bool_op // we don't need this anymore

	/** \brief store the value in a memory location
	 *  The toArray call allow to store the value in a memory location \a p
	 *  in a platform independent way.
	 *  \see FixNum::fromArray(const void *)
	 */
	void toArray(void *p) const {
	    unsigned long long temp = this->value;
	    unsigned char *buf = (unsigned char *)p;
	    buf += size;
	    for (unsigned i = 0; i != size; ++i) {
		--buf;
		*buf = temp;
		temp >>= 8;
	    }
	}

	/** \brief restore the value from a memory location
	 *  The fromArray call allow to load the value from a memory location \a p
	 *  in a platform independent way.
	 *  \see FixNum::toArray(void *)
	 */
	void fromArray(const void *p) {
	    unsigned char *buf = (unsigned char *)p;
	    value = 0;
	    for (unsigned i = 0; i != size; ++i) {
		value <<= 8;
		value |= buf[i];
	    }
	}

	friend Duration operator -(const AbsTime& a, const AbsTime& b);
	friend AbsTime  operator +(const AbsTime& a, const Duration b);
	friend AbsTime  operator -(const AbsTime& a, const Duration b);
	friend AbsTime& operator +=(AbsTime& a, const Duration b);
	friend AbsTime& operator -=(AbsTime& a, const Duration b);

    };

    /** \brief Type for representing a fixed point in time
     *  \ingroup GEA_API
     */
    class AbsTime : public FixNum {

    public:
	/** \brief get constant and fixed point in time
	 *
	 *  The value returned by AbsTime::t0() is normally used to generate
	 *  Duration objects from a given AbsTime values, e.g. to print out
	 *  a timestamp for debugging purposes.
	 *  \note The actual value returned is not specified and may change between
	 *        different runs of your program.
	 */
	static inline AbsTime t0() {
	    AbsTime retval;
	    retval.setNanoSecs(0);
	    return retval;
	}

	/** \brief Get the current time.
	 *
	 *  An AbsTime object is returned that represents the current time.
	 *  The time is the real (wall clock) time of the system, which requires an
	 *  expensive system call.
	 *  Often, it is better to use the time the last GEA event was triggered.
	 *  Please use GEA.lastEventTime in this case.
	 *
	 *  \see GEA.lastEventTime
	 */
	static AbsTime now() { AbsTime ret; GEA_apiIface->getCurrentTime(&ret); return ret; }

    public:

	/** \brief default constructor that does nothing */
	AbsTime() : FixNum() {}

	/** \brief copy constructor
	 */
	AbsTime(const AbsTime& other) : FixNum(other) {}

	/** \brief assignment operator
	 */
	AbsTime& operator =(const AbsTime& other) { FixNum::operator =(other); return *this; }

    }; // end class AbsTime

    /**
     *  \brief class representing the delta of two AbsTime objects.
     *  \ingroup GEA_API
     *
     *  The duration class is used to represent time spans. It defines operators
     *  to use it in a convinient way with the class gea::AbsTime.
     */
    class Duration : public FixNum {

    public:

	/** \brief default constructor
	 *
	 *  The default value of the object is undefined. This way we can detect
	 *  uninitialised values with tools like valgrind.
	 */
	Duration() :
	    FixNum()
	{}

	/** \brief copy constructor */
	Duration(const Duration& d) :
	    FixNum(d) {}

	/** \brief initialise from double
	 *
	 *  The duration will have the value of \a t seconds.
	 */
	explicit Duration(double t)
	{
	    value = static_cast<StoreType>( 1.e9 * t );
	}

	/** \brief Initialise from a rational number
	 *
	 *  The duration will have the value of a/b seconds.
	 *  \code
	 *  Duration one_fourth(1,4);
	 *  \endcode
	 *  will create a duration of 0.25 (1/4) second. This avoids the use of floating point operations.
	 */
	explicit Duration(long a, long b)
	{
	    setNanoSecs((long long)a * 1000000000LL);
	    value /= (StoreType)b;
	}

	/** \brief multiply duration with integer */
	Duration& operator *=(long m) {
	    this->value *= (StoreType)m;
	    return *this;
	}

	/** \brief multiply duration with integer */
	Duration operator *(long m) const {
	    Duration ret = *this;
	    ret *= m;
	    return ret;
	}

    }; // end class Duration


    /** \brief calculate the difference between two absolute times.
     *  \ingroup GEA_API
     */
    static inline Duration operator -(const AbsTime& a, const AbsTime& b) {
	Duration ret;
	ret.value = a.value - b.value;
	return ret;
    }

    /** \brief add a duration to an absolute time.
     *  \ingroup GEA_API
     */
    static inline AbsTime& operator +=(AbsTime& a, const Duration b) {
	a.value += b.value;
	return a;
    }

    /** \brief substract a duration from an absolute time.
     *  \ingroup GEA_API
     *
     */
    static inline AbsTime& operator -=(AbsTime& a, const Duration b) {
	a.value -= b.value;
	return a;
    }

    /** \brief add a duration to an absolute time.
     *  \ingroup GEA_API
     */
    static inline AbsTime operator +(const AbsTime& a, const Duration b) {
	AbsTime ret = a;
	ret.value += b.value;
	return ret;
    }

    /** \brief substract a duration from an absolute time.
     *  \ingroup GEA_API
     *
     */
    static inline AbsTime operator -(const AbsTime& a, const Duration b) {
	AbsTime ret = a;
	ret.value -= b.value;
	return ret;
    }

} // end of namespace gea


#endif //_GEATIME_H__
/* This stuff is for emacs
 * Local variables:
 * mode:c++
 * c-basic-offset: 4
 * End:
 */
