#include "modules/mapping.hpp"

#include <boost/python.hpp>

namespace bp = boost::python;

// TODO: template with record type
void export_metric_KOC() {
    using Record = std::vector<double>;
    using Factory = metric::KOC_factory<Record>;
    using KOC = Factory::KOC;

    auto factory = bp::class_<Factory>("KOC_factory");

    factory.def(
        bp::init<size_t, double, double, size_t, Factory::T, Factory::T>(
            (
                bp::arg("nodesNumber"),
                bp::arg("start_learn_rate")= 0.8,
                bp::arg("finish_learn_rate") = 0.0,
                bp::arg("iterations") = 20,
                bp::arg("distribution_min") = -1,
                bp::arg("distribution_max") = 1
            )
        )
    );
    factory.def(
        bp::init<size_t, size_t, double, double, size_t, Factory::T, Factory::T>(
            (
                bp::arg("nodesWidth") = 5,
                bp::arg("nodesHeight") = 4,
                bp::arg("start_learn_rate") = 0.8,
                bp::arg("finish_learn_rate") = 0.0,
                bp::arg("iterations") = 20,
                bp::arg("distribution_min") = -1,
                bp::arg("distribution_max") = 1
            )
        )
    );
    factory.def(
        bp::init<size_t, double, double, size_t, Factory::T, Factory::T, double, double, long long>(
            (
                bp::arg("nodesNumber"),
                bp::arg("start_learn_rate"),
                bp::arg("finish_learn_rate"),
                bp::arg("iterations"),
                bp::arg("distribution_min"),
                bp::arg("distribution_max"),
                bp::arg("neighborhood_start_size"),
                bp::arg("neigbour_range_decay"),
                bp::arg("random_seed")
            )
        )
    );
    factory.def(
        bp::init<size_t, size_t, double, double, size_t, Factory::T, Factory::T, double, double, long long>(
            (
                bp::arg("nodesWidth"),
                bp::arg("nodesHeight"),
                bp::arg("start_learn_rate"),
                bp::arg("finish_learn_rate"),
                bp::arg("iterations"),
                bp::arg("distribution_min"),
                bp::arg("distribution_max"),
                bp::arg("neighborhood_start_size"),
                bp::arg("neigbour_range_decay"),
                bp::arg("random_seed")
            )
        )
    );

    factory.def("__call__", &Factory::operator(), "construct KOC");

    std::vector<bool> (KOC::*check_if_anomaly1)(const std::vector<Record>&, double) = &KOC::check_if_anomaly;
    bool (KOC::*check_if_anomaly2)(const Record&, double) = &KOC::check_if_anomaly;

    // KOC
    auto koc = bp::class_<KOC>("KOC", bp::no_init);
    koc.def("train", &Factory::KOC::train);
    koc.def("result", &Factory::KOC::result);
    koc.def<std::vector<int> (KOC::*)(const std::vector<Record>&, double)>("encode", &KOC::encode);
    koc.def("check_if_anomaly", check_if_anomaly1, (bp::arg("samples"), bp::arg("anomaly_threshold") = 0.0));
    koc.def("check_if_anomaly", check_if_anomaly2, (bp::arg("sample"), bp::arg("anomaly_threshold") = 0.0));
}

// make build && pip uninstall --yes metric && pip install dist/metric-0.0.1-cp36-cp36m-linux_x86_64.whl

BOOST_PYTHON_MODULE(_KOC) {
    export_metric_KOC();
}