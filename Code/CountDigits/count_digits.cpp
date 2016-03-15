#include <iostream>
#include <array>
#include <random>
#include <boost/program_options.hpp>
#include <iomanip>

using int_t = long long int;

struct hist {
    std::array<int_t,10> bars;
    using const_iterator = std::array<int_t,10>::const_iterator;

    hist()
        : bars()
    {}

    void inc(int channel) {
        ++bars[channel];
    }

    void reset(int channel) {
        bars = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    }

    int_t operator[](int i) const {
        return bars[i];
    }


    const_iterator begin() const {return bars.begin();}
    const_iterator end() const {return bars.end();}
};

std::string getbar(int_t value) {
    std::string res;
    for (int_t i = 0; i < value; ++i) {
        res += "*";
    }
    return res;
}

std::ostream& operator<<(std::ostream& s, hist const& v) {
    long long int tot = 0;
    for (int_t i: v) {
        //s << "blabla i " << i << " tot " << tot << "\n";
        tot += i;
    }
    s << "Total samples: " << tot << "\n";
    int k = 0;
    for (int_t i: v) {
        //s << "i " << i << " tot " << tot << "\n";
        //s << "i " << static_cast<double>(i) << " tot " << static_cast<double>(tot) << "\n";


        auto val = static_cast<double>(i)/static_cast<double>(tot)*100.;
        s << k++ << ": " << std::setprecision(3) << std::setw(4) << val << ": " << getbar(val) << "\n";
    }
    return s;
}

inline void add_digits(int value, hist & histogram) {
    while (value > 0) {
        histogram.inc(value % 10);
        value /= 10;
    }
}

int main(int argc, char** argv) {
    namespace po = boost::program_options;

    po::options_description desc_commandline;
    desc_commandline.add_options()
        ("r", po::value<int>()->default_value(50000), "Samples from 1 to 'r'")
        ("n", po::value<int>()->default_value(10000), "Number of samples")
        ("c", po::value<int>()->default_value(8), "Maximum number of elements to sum");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc_commandline), vm);

    int range = vm["r"].as<int>();
    int n_samples = vm["n"].as<int>();
    int n_sums = vm["c"].as<int>();

    // assure n_samples is multiple of n_sums
    n_samples -= n_samples % n_sums;

    if (n_samples <= 0) {
        std::cout << "n_samples should be much larger than number of elements to sum for statistical significance\n";
        std::cout << "Adjusted number of samples: " << n_samples << "\n";
        std::cout << "Number of sums            : " << n_sums << "\n";
        std::exit(1);
    }

    std::cout << "Adjusted number of samples: " << n_samples << "\n";
    std::cout << "Number of sums            : " << n_sums << "\n";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, range);

    std::vector<int> data(n_samples);

    int count = 1;
    std::for_each(data.begin(), data.end(), [&count,range, &dis, &gen] (int &value) {
#ifdef TEST
            value = count%(range+1); ++count;
#else
            value=dis(gen);
#endif
        });

#ifndef NDEBUG
    std::for_each(data.begin(), data.end(), [&count] (int value) { std::cout << value << std::endl;});
#endif
    //        data.push_back(dis(gen));


    std::vector<hist> histograms;

    for (int i = 1; i <= n_sums; ++i) {
        hist histogram;
#ifndef NDEBUG
        std::cout << "Sums " << i << (i==1?"value":"values") << std::endl;
#endif
        for (int k = 0; k < data.size(); k+=i) {
            int_t new_value = 0;
            int j = 0;
            while (k+j < data.size() && j<i)  {
#ifndef NDEBUG
                std::cout << new_value << " + " << data[k+j] << " = " << new_value+data[k+j] << std::endl;
#endif
                new_value += data[k+j];
                ++j;
            }
            add_digits(new_value, histogram);
        }
        histograms.push_back(histogram);
    }

    std::for_each(histograms.begin(), histograms.end(), [](hist const& h) { std::cout << h << std::endl;});

}
