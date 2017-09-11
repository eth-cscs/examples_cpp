#include "../show.h"

namespace units {
    struct unit {
        double v;

        unit(long double x) : v(x) { }
    };

    /************/
    /* DISTANCE */
    /************/
    struct distance : public unit {
        using unit::unit;
    };

    struct m : public distance {
        using distance::distance;
        static std::string name() {return "m";}
        static constexpr double to_fundamental() {return 1;}
    };

    struct km : public distance {
        using distance::distance;

        operator m() const { return m{v * 1000}; }
        static std::string name() {return "km";}
        static constexpr double to_fundamental() {return 1000;}
    };

    struct mm : public distance {
        using distance::distance;

        operator m() const { return m{v / 1000}; }
        static std::string name() {return "mm";}
        static constexpr double to_fundamental() {return 1e-3;}
    };

    /********/
    /* TIME */
    /********/
    struct time : public unit {
        using unit::unit;
    };

    struct s : public time {
        using time::time;

        static std::string name() {return "s";}
        static constexpr double to_fundamental() {return 1;}
    };

    struct hrs : public time {
        using time::time;

        operator s() const { return s{v * 3600}; }
        static std::string name() {return "hrs";}
        static constexpr double to_fundamental() {return 3600;}
    };

    struct min : public time {
        using time::time;

        operator s() const { return s{v * 60}; }
        static std::string name() {return "min";}
        static constexpr double to_fundamental() {return 60;}
    };

    /************
     * VELOCITY *
     ************/
    template <typename D, typename T>
    struct vel : public unit {
        using unit::unit;
        static std::string name() {return D::name() + "/" + T::name();}

        template <typename DD, typename TT>
        operator vel<DD,TT>() const {
                return v * D::to_fundamental()/DD::to_fundamental() / T::to_fundamental()*TT::to_fundamental();
        };
    };

    template<typename T>
    T operator+(T a, T b) { return T{a.v + b.v}; }

    template <typename Dist, typename Time>
    typename std::enable_if<std::is_base_of<distance, Dist>::value and std::is_base_of<time, Time>::value, vel<Dist, Time> >::type
    operator/(Dist const &d, Time const &t) {
        return d.v / t.v;
    }

    template<typename T>
    typename std::enable_if<std::is_base_of<unit, T>::value, std::ostream>::type &
    operator<<(std::ostream &s, T x) {
        return s << x.v << T::name();
    }
} // namespace units

units::km operator""_km(long double v) { return units::km{v}; }

units::m operator""_m(long double v) { return units::m{v}; }

units::mm operator""_mm(long double v) { return units::mm{v}; }

units::s operator""_s(long double v) { return units::s{v}; }

units::hrs operator""_h(long double v) { return units::hrs{v}; }

units::min operator""_min(long double v) { return units::min{v}; }

int main() {
    using namespace units;
    km x = 12;
    auto y = x + 8.5_km;
    SHOW(y);
    SHOW((10._km) / (1._h))
    SHOW((static_cast<vel<m,s>>(10._km/1._h)));
}
