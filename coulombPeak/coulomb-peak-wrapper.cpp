#include "peak-finding/peak-finding.hpp"
#include <falcon-core/math/Quantity.hpp>
#include <falcon-core/math/arrays/LabelledControlArray.hpp>
#include <falcon-core/math/arrays/LabelledMeasuredArray.hpp>
#include <falcon-typing/FFIHelpers.hpp>

using namespace falcon::typing;
using namespace falcon::typing::ffi::wrapper;
using namespace falcon_core::math;
using namespace falcon_core::math::arrays;
using namespace falcon_core::physics::units;
using namespace findPeaks;

static void pack_array_result(std::shared_ptr<ArrayValue> arr,
                              FalconResultSlot *out, int32_t *oc) {
  out[0] = {};
  out[0].tag = FALCON_TYPE_OPAQUE;
  out[0].value.opaque.type_name = "Array";
  out[0].value.opaque.ptr =
      new std::shared_ptr<void>(std::static_pointer_cast<void>(arr));
  out[0].value.opaque.deleter = [](void *p) {
    delete static_cast<std::shared_ptr<void> *>(p);
  };
  *oc = 1;
}

static RuntimeValue wrap_q_as_struct(QuantitySP quan) {
  auto inst = std::make_shared<StructInstance>("Quantity");
  inst->native_handle = std::static_pointer_cast<void>(quan);
  return inst;
}

extern "C" {
// routine HardCodedPeakFit (labelledcontrolarray::LabelledControlArray xarray,
// labelledmeasuredArray::LabelledMeasuredArray yarray) ->
// (array::Array<quantity::Quantity> voltages)
void HardCodedPeakFit(const FalconParamEntry *params, int32_t param_count,
                      FalconResultSlot *out, int32_t *oc) {
  auto xarray = get_opaque<LabelledControlArray>(params, param_count, "xarray");
  auto yarray =
      get_opaque<LabelledMeasuredArray>(params, param_count, "yarray");

  PeakConditions conditions;
  conditions.set_prominence(0.01);
  conditions.set_distance(2);
  std::vector<peak_result_t> peaks =
      find_peaks(yarray->data().data(), conditions);

  std::vector<RuntimeValue> elements;
  if (!peaks.empty()) {
    elements.reserve(peaks.size());
    for (const auto &peak : peaks) {
      size_t peak_location = peak.peak;
      double voltage = xarray->data()[peak_location];
      SymbolUnitSP unit = xarray->units();
      QuantitySP quan = std::make_shared<Quantity>(voltage, unit);
      elements.push_back(wrap_q_as_struct(quan));
    }
  }
  auto arr_val = std::make_shared<ArrayValue>("Quantity", std::move(elements));
  pack_array_result(arr_val, out, oc);
}
}
