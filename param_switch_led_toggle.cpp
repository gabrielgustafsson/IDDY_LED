/*******************************************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER $200k in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below $200k annual revenue or funding.

For entities with OVER $200k in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing@cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/10730637742483-RNBO-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
*******************************************************************************************************************/

#include "RNBO_Common.h"
#include "RNBO_AudioSignal.h"

namespace RNBO {


#define trunc(x) ((Int)(x))

#if defined(__GNUC__) || defined(__clang__)
    #define RNBO_RESTRICT __restrict__
#elif defined(_MSC_VER)
    #define RNBO_RESTRICT __restrict
#endif

#define FIXEDSIZEARRAYINIT(...) { }

class rnbomatic : public PatcherInterfaceImpl {
public:

class RNBOSubpatcher_3775 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    class RNBOSubpatcher_3774 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_3775;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_3774()
            {
            }
            
            ~RNBOSubpatcher_3774()
            {
            }
            
            virtual RNBOSubpatcher_3775* getPatcher() const {
                return static_cast<RNBOSubpatcher_3775 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
                getEngine()->flushClockEvents(this, -1494586265, false);
            }
            
            number mstosamps(MillisecondTime ms) {
                return ms * this->sr * 0.001;
            }
            
            Index voice() {
                return this->_voiceIndex;
            }
            
            number random(number low, number high) {
                number range = high - low;
                return rand01() * range + low;
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                SampleValue * out3 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
                this->noise_tilde_01_perform(this->signals[0], n);
                this->dspexpr_01_perform(this->signals[0], this->signals[1], n);
                this->changetilde_01_perform(in1, this->signals[0], n);
                this->dspexpr_02_perform(this->signals[0], this->signals[2], n);
            
                this->sah_tilde_01_perform(
                    this->signals[1],
                    this->signals[2],
                    this->sah_tilde_01_thresh,
                    this->signals[0],
                    n
                );
            
                this->dspexpr_03_perform(this->signals[0], this->dspexpr_03_in2, this->signals[1], n);
                this->latch_tilde_01_perform(this->signals[2], this->signals[1], out3, n);
                this->numbertilde_01_perform(this->signals[0], this->dummyBuffer, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    Index i;
            
                    for (i = 0; i < 3; i++) {
                        this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                    }
            
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                this->latch_tilde_01_dspsetup(forceDSPSetup);
                this->numbertilde_01_dspsetup(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    {
                    this->setProbingIndex(-1);
                    break;
                    }
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& ) {}
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime , TransportState ) {}
            
            void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime , int , int ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                default:
                    {
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
                RNBO_UNUSED(hasValue);
                this->updateTime(time);
            
                switch (index) {
                case -1494586265:
                    {
                    this->numbertilde_01_value_set(value);
                    break;
                    }
                }
            }
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
                this->updateTime(time);
            
                switch (tag) {
                case TAG("sig"):
                    {
                    if (TAG("rotating_clock_divider[1]/probability_skip/number~_obj-77") == objectId)
                        this->numbertilde_01_sig_number_set(payload);
            
                    break;
                    }
                case TAG("mode"):
                    {
                    if (TAG("rotating_clock_divider[1]/probability_skip/number~_obj-77") == objectId)
                        this->numbertilde_01_mode_set(payload);
            
                    break;
                    }
                }
            }
            
            void processListMessage(
                MessageTag tag,
                MessageTag objectId,
                MillisecondTime time,
                const list& payload
            ) {
                this->updateTime(time);
            
                switch (tag) {
                case TAG("sig"):
                    {
                    if (TAG("rotating_clock_divider[1]/probability_skip/number~_obj-77") == objectId)
                        this->numbertilde_01_sig_list_set(payload);
            
                    break;
                    }
                }
            }
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
                case TAG("monitor"):
                    {
                    return "monitor";
                    }
                case TAG("rotating_clock_divider[1]/probability_skip/number~_obj-77"):
                    {
                    return "rotating_clock_divider[1]/probability_skip/number~_obj-77";
                    }
                case TAG("assign"):
                    {
                    return "assign";
                    }
                case TAG("setup"):
                    {
                    return "setup";
                    }
                case TAG("sig"):
                    {
                    return "sig";
                    }
                case TAG("mode"):
                    {
                    return "mode";
                    }
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
            
            void initialize() {
                this->assign_defaults();
                this->setState();
            }
            
            protected:
            
            void numbertilde_01_sig_number_set(number v) {
                this->numbertilde_01_outValue = v;
            }
            
            void numbertilde_01_sig_list_set(const list& v) {
                this->numbertilde_01_outValue = v[0];
            }
            
            void numbertilde_01_mode_set(number v) {
                if (v == 1) {
                    this->numbertilde_01_currentMode = 0;
                } else if (v == 2) {
                    this->numbertilde_01_currentMode = 1;
                }
            }
            
            void eventinlet_01_out1_bang_bang() {
                this->expr_01_in1_bang();
            }
            
            void eventinlet_01_out1_list_set(const list& v) {
                {
                    if (v->length > 1)
                        this->expr_01_in2_set(v[1]);
            
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->expr_01_in1_set(converted);
                }
            }
            
            void numbertilde_01_value_set(number ) {}
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 1;
            }
            
            Index getNumOutputChannels() const {
                return 1;
            }
            
            void initializeObjects() {
                this->numbertilde_01_init();
                this->noise_tilde_01_init();
                this->changetilde_01_ch_init();
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void allocateDataRefs() {}
            
            void dspexpr_03_in2_set(number v) {
                this->dspexpr_03_in2 = v;
            }
            
            void sah_tilde_01_thresh_set(number v) {
                this->sah_tilde_01_thresh = v;
            }
            
            void expr_02_out1_set(number v) {
                this->expr_02_out1 = v;
                this->dspexpr_03_in2_set(this->expr_02_out1);
                this->sah_tilde_01_thresh_set(this->expr_02_out1);
            }
            
            void expr_02_in1_set(number in1) {
                this->expr_02_in1 = in1;
                this->expr_02_out1_set(this->expr_02_in1 - this->expr_02_in2);//#map:rotating_clock_divider[1]/probability_skip/-_obj-5:1
            }
            
            void expr_01_out1_set(number v) {
                this->expr_01_out1 = v;
                this->expr_02_in1_set(this->expr_01_out1);
            }
            
            void expr_01_in1_set(number in1) {
                this->expr_01_in1 = in1;
                this->expr_01_out1_set(this->expr_01_in1 + this->expr_01_in2);//#map:rotating_clock_divider[1]/probability_skip/+_obj-6:1
            }
            
            void eventinlet_01_out1_number_set(number v) {
                this->expr_01_in1_set(v);
            }
            
            void expr_01_in1_bang() {
                this->expr_01_out1_set(this->expr_01_in1 + this->expr_01_in2);//#map:rotating_clock_divider[1]/probability_skip/+_obj-6:1
            }
            
            void expr_01_in2_set(number v) {
                this->expr_01_in2 = v;
            }
            
            void noise_tilde_01_perform(SampleValue * out1, Index n) {
                auto __noise_tilde_01_state = this->noise_tilde_01_state;
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = xoshiro_next(__noise_tilde_01_state);
                }
            }
            
            void dspexpr_01_perform(const Sample * in1, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = rnbo_abs(in1[(Index)i]);//#map:_###_obj_###_:1
                }
            }
            
            void changetilde_01_perform(const Sample * input, SampleValue * out, Index n) {
                for (Index i = 0; i < n; i++) {
                    out[(Index)i] = this->changetilde_01_ch_next(input[(Index)i]);
                }
            }
            
            void dspexpr_02_perform(const Sample * in1, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = rnbo_abs(in1[(Index)i]);//#map:_###_obj_###_:1
                }
            }
            
            void sah_tilde_01_perform(
                const Sample * input,
                const Sample * trig,
                number thresh,
                SampleValue * out,
                Index n
            ) {
                for (Index i = 0; i < n; i++) {
                    out[(Index)i] = this->sah_tilde_01_s_next(input[(Index)i], trig[(Index)i], thresh);
                }
            }
            
            void dspexpr_03_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] >= in2;//#map:_###_obj_###_:1
                }
            }
            
            void latch_tilde_01_perform(const Sample * x, const Sample * control, SampleValue * out1, Index n) {
                auto __latch_tilde_01_value = this->latch_tilde_01_value;
                Index i;
            
                for (i = 0; i < n; i++) {
                    if (control[(Index)i] != 0.)
                        __latch_tilde_01_value = x[(Index)i];
            
                    out1[(Index)i] = __latch_tilde_01_value;
                }
            
                this->latch_tilde_01_value = __latch_tilde_01_value;
            }
            
            void numbertilde_01_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
                auto __numbertilde_01_currentIntervalInSamples = this->numbertilde_01_currentIntervalInSamples;
                auto __numbertilde_01_lastValue = this->numbertilde_01_lastValue;
                auto __numbertilde_01_currentInterval = this->numbertilde_01_currentInterval;
                auto __numbertilde_01_rampInSamples = this->numbertilde_01_rampInSamples;
                auto __numbertilde_01_outValue = this->numbertilde_01_outValue;
                auto __numbertilde_01_currentMode = this->numbertilde_01_currentMode;
                number monitorvalue = input_signal[0];
            
                for (Index i = 0; i < n; i++) {
                    if (__numbertilde_01_currentMode == 0) {
                        output[(Index)i] = this->numbertilde_01_smooth_next(
                            __numbertilde_01_outValue,
                            __numbertilde_01_rampInSamples,
                            __numbertilde_01_rampInSamples
                        );
                    } else {
                        output[(Index)i] = input_signal[(Index)i];
                    }
                }
            
                __numbertilde_01_currentInterval -= n;
            
                if (monitorvalue != __numbertilde_01_lastValue && __numbertilde_01_currentInterval <= 0) {
                    __numbertilde_01_currentInterval = __numbertilde_01_currentIntervalInSamples;
            
                    this->getEngine()->scheduleClockEventWithValue(
                        this,
                        -1494586265,
                        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                        monitorvalue
                    );;
            
                    __numbertilde_01_lastValue = monitorvalue;
            
                    this->getEngine()->sendListMessage(
                        TAG("monitor"),
                        TAG("rotating_clock_divider[1]/probability_skip/number~_obj-77"),
                        {monitorvalue},
                        this->_currentTime
                    );;
                }
            
                this->numbertilde_01_currentInterval = __numbertilde_01_currentInterval;
                this->numbertilde_01_lastValue = __numbertilde_01_lastValue;
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            void latch_tilde_01_reset() {
                this->latch_tilde_01_value = 0;
            }
            
            void latch_tilde_01_dspsetup(bool force) {
                if ((bool)(this->latch_tilde_01_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->latch_tilde_01_reset();
                this->latch_tilde_01_setupDone = true;
            }
            
            number numbertilde_01_smooth_d_next(number x) {
                number temp = (number)(x - this->numbertilde_01_smooth_d_prev);
                this->numbertilde_01_smooth_d_prev = x;
                return temp;
            }
            
            void numbertilde_01_smooth_d_dspsetup() {
                this->numbertilde_01_smooth_d_reset();
            }
            
            void numbertilde_01_smooth_d_reset() {
                this->numbertilde_01_smooth_d_prev = 0;
            }
            
            number numbertilde_01_smooth_next(number x, number up, number down) {
                if (this->numbertilde_01_smooth_d_next(x) != 0.) {
                    if (x > this->numbertilde_01_smooth_prev) {
                        number _up = up;
            
                        if (_up < 1)
                            _up = 1;
            
                        this->numbertilde_01_smooth_index = _up;
                        this->numbertilde_01_smooth_increment = (x - this->numbertilde_01_smooth_prev) / _up;
                    } else if (x < this->numbertilde_01_smooth_prev) {
                        number _down = down;
            
                        if (_down < 1)
                            _down = 1;
            
                        this->numbertilde_01_smooth_index = _down;
                        this->numbertilde_01_smooth_increment = (x - this->numbertilde_01_smooth_prev) / _down;
                    }
                }
            
                if (this->numbertilde_01_smooth_index > 0) {
                    this->numbertilde_01_smooth_prev += this->numbertilde_01_smooth_increment;
                    this->numbertilde_01_smooth_index -= 1;
                } else {
                    this->numbertilde_01_smooth_prev = x;
                }
            
                return this->numbertilde_01_smooth_prev;
            }
            
            void numbertilde_01_smooth_reset() {
                this->numbertilde_01_smooth_prev = 0;
                this->numbertilde_01_smooth_index = 0;
                this->numbertilde_01_smooth_increment = 0;
                this->numbertilde_01_smooth_d_reset();
            }
            
            void numbertilde_01_init() {
                this->numbertilde_01_currentMode = 1;
            
                this->getEngine()->sendNumMessage(
                    TAG("setup"),
                    TAG("rotating_clock_divider[1]/probability_skip/number~_obj-77"),
                    1,
                    this->_currentTime
                );
            }
            
            void numbertilde_01_dspsetup(bool force) {
                if ((bool)(this->numbertilde_01_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->numbertilde_01_currentIntervalInSamples = this->mstosamps(100);
                this->numbertilde_01_currentInterval = this->numbertilde_01_currentIntervalInSamples;
                this->numbertilde_01_rampInSamples = this->mstosamps(this->numbertilde_01_ramp);
                this->numbertilde_01_setupDone = true;
                this->numbertilde_01_smooth_d_dspsetup();
            }
            
            number sah_tilde_01_s_next(number x, number trig, number thresh) {
                if (this->sah_tilde_01_s_prev <= thresh && trig > thresh)
                    this->sah_tilde_01_s_value = x;
            
                this->sah_tilde_01_s_prev = trig;
                return this->sah_tilde_01_s_value;
            }
            
            void sah_tilde_01_s_reset() {
                this->sah_tilde_01_s_prev = 0.;
                this->sah_tilde_01_s_value = 0.;
            }
            
            void noise_tilde_01_init() {
                this->noise_tilde_01_reset();
            }
            
            void noise_tilde_01_reset() {
                xoshiro_reset(
                    systemticks() + this->voice() + this->random(0, 10000),
                    this->noise_tilde_01_state
                );
            }
            
            number changetilde_01_ch_next(number x) {
                number temp = x - this->changetilde_01_ch_prev;
                this->changetilde_01_ch_prev = x;
                return (temp > 0. ? 1. : (temp < 0. ? -1. : 0));
            }
            
            void changetilde_01_ch_init() {
                this->changetilde_01_ch_prev = 0;
            }
            
            void changetilde_01_ch_reset() {
                this->changetilde_01_ch_prev = 0;
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                latch_tilde_01_x = 0;
                latch_tilde_01_control = 0;
                numbertilde_01_input_number = 0;
                numbertilde_01_ramp = 0;
                dspexpr_01_in1 = 0;
                sah_tilde_01_input = 0;
                sah_tilde_01_trig = -1;
                sah_tilde_01_thresh = 0.5;
                changetilde_01_input = 0;
                dspexpr_02_in1 = 0;
                dspexpr_03_in1 = 0;
                dspexpr_03_in2 = 0;
                expr_01_in1 = 0;
                expr_01_in2 = 1;
                expr_01_out1 = 0;
                expr_02_in1 = 0;
                expr_02_in2 = 1;
                expr_02_out1 = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                signals[0] = nullptr;
                signals[1] = nullptr;
                signals[2] = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                latch_tilde_01_value = 0;
                latch_tilde_01_setupDone = false;
                numbertilde_01_currentInterval = 0;
                numbertilde_01_currentIntervalInSamples = 0;
                numbertilde_01_lastValue = 0;
                numbertilde_01_outValue = 0;
                numbertilde_01_rampInSamples = 0;
                numbertilde_01_currentMode = 0;
                numbertilde_01_smooth_d_prev = 0;
                numbertilde_01_smooth_prev = 0;
                numbertilde_01_smooth_index = 0;
                numbertilde_01_smooth_increment = 0;
                numbertilde_01_setupDone = false;
                sah_tilde_01_s_prev = 0;
                sah_tilde_01_s_value = 0;
                changetilde_01_ch_prev = 0;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number latch_tilde_01_x;
                number latch_tilde_01_control;
                number numbertilde_01_input_number;
                number numbertilde_01_ramp;
                number dspexpr_01_in1;
                number sah_tilde_01_input;
                number sah_tilde_01_trig;
                number sah_tilde_01_thresh;
                number changetilde_01_input;
                number dspexpr_02_in1;
                number dspexpr_03_in1;
                number dspexpr_03_in2;
                number expr_01_in1;
                number expr_01_in2;
                number expr_01_out1;
                number expr_02_in1;
                number expr_02_in2;
                number expr_02_out1;
                MillisecondTime _currentTime;
                SampleIndex audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                SampleValue * signals[3];
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number latch_tilde_01_value;
                bool latch_tilde_01_setupDone;
                SampleIndex numbertilde_01_currentInterval;
                SampleIndex numbertilde_01_currentIntervalInSamples;
                number numbertilde_01_lastValue;
                number numbertilde_01_outValue;
                number numbertilde_01_rampInSamples;
                Int numbertilde_01_currentMode;
                number numbertilde_01_smooth_d_prev;
                number numbertilde_01_smooth_prev;
                number numbertilde_01_smooth_index;
                number numbertilde_01_smooth_increment;
                bool numbertilde_01_setupDone;
                number sah_tilde_01_s_prev;
                number sah_tilde_01_s_value;
                UInt noise_tilde_01_state[4] = { };
                number changetilde_01_ch_prev;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    RNBOSubpatcher_3775()
    {
    }
    
    ~RNBOSubpatcher_3775()
    {
        delete this->p_01;
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, 1964277200, false);
        getEngine()->flushClockEvents(this, -871642103, false);
        getEngine()->flushClockEvents(this, 1592269969, false);
        getEngine()->flushClockEvents(this, 1220262738, false);
        getEngine()->flushClockEvents(this, 848255507, false);
    }
    
    inline number safemod(number f, number m) {
        if (m != 0) {
            Int f_trunc = (Int)(trunc(f));
            Int m_trunc = (Int)(trunc(m));
    
            if (f == f_trunc && m == m_trunc) {
                f = f_trunc % m_trunc;
            } else {
                if (m < 0) {
                    m = -m;
                }
    
                if (f >= m) {
                    if (f >= m * 2.0) {
                        number d = f / m;
                        Int i = (Int)(trunc(d));
                        d = d - i;
                        f = d * m;
                    } else {
                        f -= m;
                    }
                } else if (f <= -m) {
                    if (f <= -m * 2.0) {
                        number d = f / m;
                        Int i = (Int)(trunc(d));
                        d = d - i;
                        f = d * m;
                    } else {
                        f += m;
                    }
                }
            }
        } else {
            f = 0.0;
        }
    
        return f;
    }
    
    inline number safediv(number num, number denom) {
        return (denom == 0.0 ? 0.0 : num / denom);
    }
    
    number quantize(number value, number quantum) {
        return rnbo_floor(value * quantum + 0.5) / quantum;
    }
    
    MillisecondTime currenttime() {
        return this->_currentTime;
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out3 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out4 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        SampleValue * out5 = (numOutputs >= 3 && outputs[2] ? outputs[2] : this->dummyBuffer);
        SampleValue * out6 = (numOutputs >= 4 && outputs[3] ? outputs[3] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        this->rate_tilde_03_perform(in1, this->rate_tilde_03_multiplier, this->signals[0], n);
    
        this->wrap_tilde_03_perform(
            this->signals[0],
            this->wrap_tilde_03_low,
            this->wrap_tilde_03_high,
            this->signals[1],
            n
        );
    
        this->delta_tilde_03_perform(this->signals[1], this->signals[0], n);
        this->dspexpr_06_perform(this->signals[0], this->dspexpr_06_in2, this->signals[1], n);
        this->gen_04_perform(this->signals[1], out5, n);
        this->rate_tilde_04_perform(in1, this->rate_tilde_04_multiplier, this->signals[1], n);
    
        this->wrap_tilde_04_perform(
            this->signals[1],
            this->wrap_tilde_04_low,
            this->wrap_tilde_04_high,
            this->signals[0],
            n
        );
    
        this->delta_tilde_04_perform(this->signals[0], this->signals[1], n);
        this->dspexpr_07_perform(this->signals[1], this->dspexpr_07_in2, this->signals[0], n);
        this->gen_05_perform(this->signals[0], out6, n);
        this->rate_tilde_02_perform(in1, this->rate_tilde_02_multiplier, this->signals[0], n);
    
        this->wrap_tilde_02_perform(
            this->signals[0],
            this->wrap_tilde_02_low,
            this->wrap_tilde_02_high,
            this->signals[1],
            n
        );
    
        this->delta_tilde_02_perform(this->signals[1], this->signals[0], n);
        this->dspexpr_05_perform(this->signals[0], this->dspexpr_05_in2, this->signals[1], n);
        this->gen_03_perform(this->signals[1], out4, n);
        this->rate_tilde_01_perform(in1, this->rate_tilde_01_multiplier, this->signals[1], n);
    
        this->wrap_tilde_01_perform(
            this->signals[1],
            this->wrap_tilde_01_low,
            this->wrap_tilde_01_high,
            this->signals[0],
            n
        );
    
        this->delta_tilde_01_perform(this->signals[0], this->signals[1], n);
        this->dspexpr_04_perform(this->signals[1], this->dspexpr_04_in2, this->signals[0], n);
        this->gen_02_perform(this->signals[0], this->signals[1], n);
        this->p_01_perform(this->signals[1], this->signals[0], n);
        this->gen_01_perform(this->signals[0], out3, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 2; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        this->rate_tilde_03_dspsetup(forceDSPSetup);
        this->delta_tilde_03_dspsetup(forceDSPSetup);
        this->rate_tilde_04_dspsetup(forceDSPSetup);
        this->delta_tilde_04_dspsetup(forceDSPSetup);
        this->rate_tilde_02_dspsetup(forceDSPSetup);
        this->delta_tilde_02_dspsetup(forceDSPSetup);
        this->rate_tilde_01_dspsetup(forceDSPSetup);
        this->delta_tilde_01_dspsetup(forceDSPSetup);
        this->p_01->prepareToProcess(sampleRate, maxBlockSize, force);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {
        this->p_01 = new RNBOSubpatcher_3774();
        this->p_01->setEngineAndPatcher(this->getEngine(), this);
        this->p_01->initialize();
        this->p_01->setParameterOffset(this->getParameterOffset(this->p_01));
    }
    
    void getPreset(PatcherStateInterface& preset) {
        this->param_01_getPresetValue(getSubState(preset, "slide_1"));
        this->p_01->getPreset(getSubState(getSubState(preset, "__sps"), "probability_skip"));
    }
    
    void processTempoEvent(MillisecondTime time, Tempo tempo) {
        this->updateTime(time);
        this->p_01->processTempoEvent(time, tempo);
    }
    
    void processTransportEvent(MillisecondTime time, TransportState state) {
        this->updateTime(time);
        this->p_01->processTransportEvent(time, state);
    }
    
    void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
        this->updateTime(time);
        this->p_01->processBeatTimeEvent(time, beattime);
    }
    
    void onSampleRateChanged(double ) {}
    
    void processTimeSignatureEvent(MillisecondTime time, int numerator, int denominator) {
        this->updateTime(time);
        this->p_01->processTimeSignatureEvent(time, numerator, denominator);
    }
    
    void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
        this->updateTime(time);
    
        switch (index) {
        case 0:
            {
            this->param_01_value_set(v);
            break;
            }
        default:
            {
            index -= 1;
    
            if (index < this->p_01->getNumParameters())
                this->p_01->setParameterValue(index, v, time);
    
            break;
            }
        }
    }
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        case 0:
            {
            return this->param_01_value;
            }
        default:
            {
            index -= 1;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->getParameterValue(index);
    
            return 0;
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 1 + this->p_01->getNumParameters();
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "slide_1";
            }
        default:
            {
            index -= 1;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->getParameterName(index);
    
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "rotating_clock_divider[1]/slide_1";
            }
        default:
            {
            index -= 1;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->getParameterId(index);
    
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
        {
            switch (index) {
            case 0:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            default:
                {
                index -= 1;
    
                if (index < this->p_01->getNumParameters())
                    this->p_01->getParameterInfo(index, info);
    
                break;
                }
            }
        }
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
        if (subpatcher == this->p_01)
            return 1;
    
        return 0;
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 0:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                ParameterValue normalizedValue = (value - 0) / (1 - 0);
                return normalizedValue;
            }
            }
        default:
            {
            index -= 1;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->convertToNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        case 0:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
                {
                    return 0 + value * (1 - 0);
                }
            }
            }
        default:
            {
            index -= 1;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->convertFromNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 0:
            {
            return this->param_01_value_constrain(value);
            }
        default:
            {
            index -= 1;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->constrainParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(hasValue);
        this->updateTime(time);
    
        switch (index) {
        case 1964277200:
            {
            this->line_01_tick_set(value);
            break;
            }
        case -871642103:
            {
            this->loadbang_01_startupbang_bang();
            break;
            }
        case 1592269969:
            {
            this->line_02_tick_set(value);
            break;
            }
        case 1220262738:
            {
            this->line_03_tick_set(value);
            break;
            }
        case 848255507:
            {
            this->line_04_tick_set(value);
            break;
            }
        }
    }
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("valin"):
            {
            if (TAG("rotating_clock_divider[1]/number_obj-66") == objectId)
                this->numberobj_01_valin_set(payload);
    
            break;
            }
        case TAG("format"):
            {
            if (TAG("rotating_clock_divider[1]/number_obj-66") == objectId)
                this->numberobj_01_format_set(payload);
    
            break;
            }
        case TAG("listin"):
            {
            if (TAG("rotating_clock_divider[1]/message_obj-82") == objectId)
                this->message_01_listin_number_set(payload);
    
            if (TAG("rotating_clock_divider[1]/message_obj-53") == objectId)
                this->message_02_listin_number_set(payload);
    
            if (TAG("rotating_clock_divider[1]/message_obj-127") == objectId)
                this->message_03_listin_number_set(payload);
    
            if (TAG("rotating_clock_divider[1]/message_obj-128") == objectId)
                this->message_04_listin_number_set(payload);
    
            if (TAG("rotating_clock_divider[1]/message_obj-129") == objectId)
                this->message_05_listin_number_set(payload);
    
            break;
            }
        }
    
        this->p_01->processNumMessage(tag, objectId, time, payload);
    }
    
    void processListMessage(
        MessageTag tag,
        MessageTag objectId,
        MillisecondTime time,
        const list& payload
    ) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("listin"):
            {
            if (TAG("rotating_clock_divider[1]/message_obj-82") == objectId)
                this->message_01_listin_list_set(payload);
    
            if (TAG("rotating_clock_divider[1]/message_obj-53") == objectId)
                this->message_02_listin_list_set(payload);
    
            if (TAG("rotating_clock_divider[1]/message_obj-127") == objectId)
                this->message_03_listin_list_set(payload);
    
            if (TAG("rotating_clock_divider[1]/message_obj-128") == objectId)
                this->message_04_listin_list_set(payload);
    
            if (TAG("rotating_clock_divider[1]/message_obj-129") == objectId)
                this->message_05_listin_list_set(payload);
    
            break;
            }
        }
    
        this->p_01->processListMessage(tag, objectId, time, payload);
    }
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("bangin"):
            {
            if (TAG("rotating_clock_divider[1]/button_obj-57") == objectId)
                this->button_01_bangin_bang();
    
            break;
            }
        case TAG("listin"):
            {
            if (TAG("rotating_clock_divider[1]/message_obj-82") == objectId)
                this->message_01_listin_bang_bang();
    
            if (TAG("rotating_clock_divider[1]/message_obj-53") == objectId)
                this->message_02_listin_bang_bang();
    
            if (TAG("rotating_clock_divider[1]/message_obj-127") == objectId)
                this->message_03_listin_bang_bang();
    
            if (TAG("rotating_clock_divider[1]/message_obj-128") == objectId)
                this->message_04_listin_bang_bang();
    
            if (TAG("rotating_clock_divider[1]/message_obj-129") == objectId)
                this->message_05_listin_bang_bang();
    
            break;
            }
        case TAG("startupbang"):
            {
            if (TAG("rotating_clock_divider[1]/loadbang_obj-168") == objectId)
                this->loadbang_01_startupbang_bang();
    
            break;
            }
        }
    
        this->p_01->processBangMessage(tag, objectId, time);
    }
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("valout"):
            {
            return "valout";
            }
        case TAG("rotating_clock_divider[1]/number_obj-66"):
            {
            return "rotating_clock_divider[1]/number_obj-66";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("bangout"):
            {
            return "bangout";
            }
        case TAG("rotating_clock_divider[1]/button_obj-57"):
            {
            return "rotating_clock_divider[1]/button_obj-57";
            }
        case TAG("listout"):
            {
            return "listout";
            }
        case TAG("rotating_clock_divider[1]/message_obj-82"):
            {
            return "rotating_clock_divider[1]/message_obj-82";
            }
        case TAG("rotating_clock_divider[1]/message_obj-53"):
            {
            return "rotating_clock_divider[1]/message_obj-53";
            }
        case TAG("rotating_clock_divider[1]/message_obj-127"):
            {
            return "rotating_clock_divider[1]/message_obj-127";
            }
        case TAG("rotating_clock_divider[1]/message_obj-128"):
            {
            return "rotating_clock_divider[1]/message_obj-128";
            }
        case TAG("rotating_clock_divider[1]/message_obj-129"):
            {
            return "rotating_clock_divider[1]/message_obj-129";
            }
        case TAG("valin"):
            {
            return "valin";
            }
        case TAG("format"):
            {
            return "format";
            }
        case TAG("bangin"):
            {
            return "bangin";
            }
        case TAG("listin"):
            {
            return "listin";
            }
        case TAG("startupbang"):
            {
            return "startupbang";
            }
        case TAG("rotating_clock_divider[1]/loadbang_obj-168"):
            {
            return "rotating_clock_divider[1]/loadbang_obj-168";
            }
        }
    
        auto subpatchResult_0 = this->p_01->resolveTag(tag);
    
        if (subpatchResult_0)
            return subpatchResult_0;
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
        this->p_01->processDataViewUpdate(index, time);
    }
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void param_01_value_set(number v) {
        v = this->param_01_value_constrain(v);
        this->param_01_value = v;
        this->sendParameter(0, false);
    
        if (this->param_01_value != this->param_01_lastValue) {
            this->getEngine()->presetTouched();
            this->param_01_lastValue = this->param_01_value;
        }
    
        this->p_01_in2_number_set(v);
    }
    
    void numberobj_01_valin_set(number v) {
        this->numberobj_01_value_set(v);
    }
    
    void numberobj_01_format_set(number v) {
        this->numberobj_01_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void button_01_bangin_bang() {
        this->button_01_bangval_bang();
    }
    
    void eventinlet_02_out1_bang_bang() {
        this->numberobj_01_value_bang();
    }
    
    void eventinlet_02_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_01_value_set(converted);
        }
    }
    
    void line_01_tick_set(number v) {
        this->line_01_output_set(v);
    
        if ((bool)(this->line_01_isFinished(v))) {
            this->line_01_slope = 0;
            this->line_01_startValue = v;
            this->line_01_startPendingRamp();
        } else {
            this->line_01_scheduleNext();
        }
    }
    
    void message_01_listin_list_set(const list& v) {
        this->message_01_set_set(v);
    }
    
    void message_01_listin_number_set(number v) {
        this->message_01_set_set(v);
    }
    
    void message_01_listin_bang_bang() {
        this->message_01_trigger_bang();
    }
    
    void loadbang_01_startupbang_bang() {
        this->loadbang_01_output_bang();
    }
    
    void message_02_listin_list_set(const list& v) {
        this->message_02_set_set(v);
    }
    
    void message_02_listin_number_set(number v) {
        this->message_02_set_set(v);
    }
    
    void message_02_listin_bang_bang() {
        this->message_02_trigger_bang();
    }
    
    void line_02_tick_set(number v) {
        this->line_02_output_set(v);
    
        if ((bool)(this->line_02_isFinished(v))) {
            this->line_02_slope = 0;
            this->line_02_startValue = v;
            this->line_02_startPendingRamp();
        } else {
            this->line_02_scheduleNext();
        }
    }
    
    void message_03_listin_list_set(const list& v) {
        this->message_03_set_set(v);
    }
    
    void message_03_listin_number_set(number v) {
        this->message_03_set_set(v);
    }
    
    void message_03_listin_bang_bang() {
        this->message_03_trigger_bang();
    }
    
    void line_03_tick_set(number v) {
        this->line_03_output_set(v);
    
        if ((bool)(this->line_03_isFinished(v))) {
            this->line_03_slope = 0;
            this->line_03_startValue = v;
            this->line_03_startPendingRamp();
        } else {
            this->line_03_scheduleNext();
        }
    }
    
    void message_04_listin_list_set(const list& v) {
        this->message_04_set_set(v);
    }
    
    void message_04_listin_number_set(number v) {
        this->message_04_set_set(v);
    }
    
    void message_04_listin_bang_bang() {
        this->message_04_trigger_bang();
    }
    
    void line_04_tick_set(number v) {
        this->line_04_output_set(v);
    
        if ((bool)(this->line_04_isFinished(v))) {
            this->line_04_slope = 0;
            this->line_04_startValue = v;
            this->line_04_startPendingRamp();
        } else {
            this->line_04_scheduleNext();
        }
    }
    
    void message_05_listin_list_set(const list& v) {
        this->message_05_set_set(v);
    }
    
    void message_05_listin_number_set(number v) {
        this->message_05_set_set(v);
    }
    
    void message_05_listin_bang_bang() {
        this->message_05_trigger_bang();
    }
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 1;
    }
    
    Index getNumOutputChannels() const {
        return 4;
    }
    
    void initializeObjects() {
        this->gen_01_counter_0_init();
        this->gen_02_counter_0_init();
        this->numberobj_01_init();
        this->message_01_init();
        this->message_02_init();
        this->gen_03_counter_0_init();
        this->message_03_init();
        this->gen_04_counter_0_init();
        this->message_04_init();
        this->gen_05_counter_0_init();
        this->message_05_init();
        this->p_01->initializeObjects();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime());
        this->p_01->startup();
        this->getEngine()->scheduleClockEvent(this, -871642103, 0 + this->_currentTime);;
    
        {
            this->scheduleParamInit(0, 0);
        }
    }
    
    void allocateDataRefs() {
        this->p_01->allocateDataRefs();
    }
    
    void listrot_01_shift_set(number v) {
        this->listrot_01_shift = v;
    }
    
    void unpack_01_out8_set(number v) {
        this->unpack_01_out8 = v;
    }
    
    void unpack_01_out7_set(number v) {
        this->unpack_01_out7 = v;
    }
    
    void unpack_01_out6_set(number v) {
        this->unpack_01_out6 = v;
    }
    
    void unpack_01_out5_set(number v) {
        this->unpack_01_out5 = v;
    }
    
    void message_05_set_set(const list& v) {
        this->message_05_set = jsCreateListCopy(v);
    
        this->getEngine()->sendListMessage(
            TAG("listout"),
            TAG("rotating_clock_divider[1]/message_obj-129"),
            v,
            this->_currentTime
        );
    }
    
    static number line_04_time_constrain(number v) {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void line_04_time_set(number v) {
        v = this->line_04_time_constrain(v);
        this->line_04_time = v;
    }
    
    void rate_tilde_04_multiplier_set(number v) {
        this->rate_tilde_04_multiplier = v;
    }
    
    void line_04_output_set(number v) {
        this->line_04_output = v;
        this->rate_tilde_04_multiplier_set(v);
    }
    
    void line_04_stop_bang() {
        this->getEngine()->flushClockEvents(this, 848255507, false);;
        this->line_04_pendingRamps->length = 0;
        this->line_04_startValue = this->line_04_output;
        this->line_04_slope = 0;
        this->line_04__time = 0;
        this->line_04_time_set(0);
    }
    
    static number line_04_grain_constrain(number v) {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void line_04_grain_set(number v) {
        v = this->line_04_grain_constrain(v);
        this->line_04_grain = v;
    
        if ((bool)(!(bool)(this->line_04_isFinished(this->line_04_startValue)))) {
            this->getEngine()->flushClockEvents(this, 848255507, false);;
            this->line_04_scheduleNext();
        }
    }
    
    void line_04_end_bang() {}
    
    void line_04_target_set(const list& v) {
        this->line_04_target = jsCreateListCopy(v);
        this->line_04_pendingRamps->length = 0;
    
        if (v->length == 1) {
            this->line_04__time = this->line_04_time;
            this->line_04_time_set(0);
    
            if ((bool)(this->line_04__time))
                this->line_04_startRamp(v[0], this->line_04__time);
            else {
                this->line_04_output_set(v[0]);
                this->line_04_startValue = v[0];
                this->line_04_stop_bang();
            }
        } else if (v->length == 2) {
            this->line_04_time_set(0);
            this->line_04__time = (v[1] < 0 ? 0 : v[1]);
            this->line_04_startRamp(v[0], this->line_04__time);
        } else if (v->length == 3) {
            this->line_04_time_set(0);
            this->line_04_grain_set(v[2]);
            this->line_04__time = (v[1] < 0 ? 0 : v[1]);
            this->line_04_startRamp(v[0], this->line_04__time);
        } else {
            this->line_04_time_set(0);
            this->line_04_pendingRamps = jsCreateListCopy(v);
            this->line_04_startPendingRamp();
        }
    }
    
    void message_05_out_set(const list& v) {
        this->line_04_target_set(v);
    }
    
    void message_05_trigger_bang() {
        this->message_05_out_set(this->message_05_set);
    }
    
    void unpack_01_out4_set(number v) {
        this->unpack_01_out4 = v;
    
        {
            list converted = {v};
            this->message_05_set_set(converted);
        }
    
        this->message_05_trigger_bang();
    }
    
    void message_04_set_set(const list& v) {
        this->message_04_set = jsCreateListCopy(v);
    
        this->getEngine()->sendListMessage(
            TAG("listout"),
            TAG("rotating_clock_divider[1]/message_obj-128"),
            v,
            this->_currentTime
        );
    }
    
    static number line_03_time_constrain(number v) {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void line_03_time_set(number v) {
        v = this->line_03_time_constrain(v);
        this->line_03_time = v;
    }
    
    void rate_tilde_03_multiplier_set(number v) {
        this->rate_tilde_03_multiplier = v;
    }
    
    void line_03_output_set(number v) {
        this->line_03_output = v;
        this->rate_tilde_03_multiplier_set(v);
    }
    
    void line_03_stop_bang() {
        this->getEngine()->flushClockEvents(this, 1220262738, false);;
        this->line_03_pendingRamps->length = 0;
        this->line_03_startValue = this->line_03_output;
        this->line_03_slope = 0;
        this->line_03__time = 0;
        this->line_03_time_set(0);
    }
    
    static number line_03_grain_constrain(number v) {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void line_03_grain_set(number v) {
        v = this->line_03_grain_constrain(v);
        this->line_03_grain = v;
    
        if ((bool)(!(bool)(this->line_03_isFinished(this->line_03_startValue)))) {
            this->getEngine()->flushClockEvents(this, 1220262738, false);;
            this->line_03_scheduleNext();
        }
    }
    
    void line_03_end_bang() {}
    
    void line_03_target_set(const list& v) {
        this->line_03_target = jsCreateListCopy(v);
        this->line_03_pendingRamps->length = 0;
    
        if (v->length == 1) {
            this->line_03__time = this->line_03_time;
            this->line_03_time_set(0);
    
            if ((bool)(this->line_03__time))
                this->line_03_startRamp(v[0], this->line_03__time);
            else {
                this->line_03_output_set(v[0]);
                this->line_03_startValue = v[0];
                this->line_03_stop_bang();
            }
        } else if (v->length == 2) {
            this->line_03_time_set(0);
            this->line_03__time = (v[1] < 0 ? 0 : v[1]);
            this->line_03_startRamp(v[0], this->line_03__time);
        } else if (v->length == 3) {
            this->line_03_time_set(0);
            this->line_03_grain_set(v[2]);
            this->line_03__time = (v[1] < 0 ? 0 : v[1]);
            this->line_03_startRamp(v[0], this->line_03__time);
        } else {
            this->line_03_time_set(0);
            this->line_03_pendingRamps = jsCreateListCopy(v);
            this->line_03_startPendingRamp();
        }
    }
    
    void message_04_out_set(const list& v) {
        this->line_03_target_set(v);
    }
    
    void message_04_trigger_bang() {
        this->message_04_out_set(this->message_04_set);
    }
    
    void unpack_01_out3_set(number v) {
        this->unpack_01_out3 = v;
    
        {
            list converted = {v};
            this->message_04_set_set(converted);
        }
    
        this->message_04_trigger_bang();
    }
    
    void message_03_set_set(const list& v) {
        this->message_03_set = jsCreateListCopy(v);
    
        this->getEngine()->sendListMessage(
            TAG("listout"),
            TAG("rotating_clock_divider[1]/message_obj-127"),
            v,
            this->_currentTime
        );
    }
    
    static number line_02_time_constrain(number v) {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void line_02_time_set(number v) {
        v = this->line_02_time_constrain(v);
        this->line_02_time = v;
    }
    
    void rate_tilde_02_multiplier_set(number v) {
        this->rate_tilde_02_multiplier = v;
    }
    
    void line_02_output_set(number v) {
        this->line_02_output = v;
        this->rate_tilde_02_multiplier_set(v);
    }
    
    void line_02_stop_bang() {
        this->getEngine()->flushClockEvents(this, 1592269969, false);;
        this->line_02_pendingRamps->length = 0;
        this->line_02_startValue = this->line_02_output;
        this->line_02_slope = 0;
        this->line_02__time = 0;
        this->line_02_time_set(0);
    }
    
    static number line_02_grain_constrain(number v) {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void line_02_grain_set(number v) {
        v = this->line_02_grain_constrain(v);
        this->line_02_grain = v;
    
        if ((bool)(!(bool)(this->line_02_isFinished(this->line_02_startValue)))) {
            this->getEngine()->flushClockEvents(this, 1592269969, false);;
            this->line_02_scheduleNext();
        }
    }
    
    void line_02_end_bang() {}
    
    void line_02_target_set(const list& v) {
        this->line_02_target = jsCreateListCopy(v);
        this->line_02_pendingRamps->length = 0;
    
        if (v->length == 1) {
            this->line_02__time = this->line_02_time;
            this->line_02_time_set(0);
    
            if ((bool)(this->line_02__time))
                this->line_02_startRamp(v[0], this->line_02__time);
            else {
                this->line_02_output_set(v[0]);
                this->line_02_startValue = v[0];
                this->line_02_stop_bang();
            }
        } else if (v->length == 2) {
            this->line_02_time_set(0);
            this->line_02__time = (v[1] < 0 ? 0 : v[1]);
            this->line_02_startRamp(v[0], this->line_02__time);
        } else if (v->length == 3) {
            this->line_02_time_set(0);
            this->line_02_grain_set(v[2]);
            this->line_02__time = (v[1] < 0 ? 0 : v[1]);
            this->line_02_startRamp(v[0], this->line_02__time);
        } else {
            this->line_02_time_set(0);
            this->line_02_pendingRamps = jsCreateListCopy(v);
            this->line_02_startPendingRamp();
        }
    }
    
    void message_03_out_set(const list& v) {
        this->line_02_target_set(v);
    }
    
    void message_03_trigger_bang() {
        this->message_03_out_set(this->message_03_set);
    }
    
    void unpack_01_out2_set(number v) {
        this->unpack_01_out2 = v;
    
        {
            list converted = {v};
            this->message_03_set_set(converted);
        }
    
        this->message_03_trigger_bang();
    }
    
    void message_01_set_set(const list& v) {
        this->message_01_set = jsCreateListCopy(v);
    
        this->getEngine()->sendListMessage(
            TAG("listout"),
            TAG("rotating_clock_divider[1]/message_obj-82"),
            v,
            this->_currentTime
        );
    }
    
    static number line_01_time_constrain(number v) {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void line_01_time_set(number v) {
        v = this->line_01_time_constrain(v);
        this->line_01_time = v;
    }
    
    void rate_tilde_01_multiplier_set(number v) {
        this->rate_tilde_01_multiplier = v;
    }
    
    void line_01_output_set(number v) {
        this->line_01_output = v;
        this->rate_tilde_01_multiplier_set(v);
    }
    
    void line_01_stop_bang() {
        this->getEngine()->flushClockEvents(this, 1964277200, false);;
        this->line_01_pendingRamps->length = 0;
        this->line_01_startValue = this->line_01_output;
        this->line_01_slope = 0;
        this->line_01__time = 0;
        this->line_01_time_set(0);
    }
    
    static number line_01_grain_constrain(number v) {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void line_01_grain_set(number v) {
        v = this->line_01_grain_constrain(v);
        this->line_01_grain = v;
    
        if ((bool)(!(bool)(this->line_01_isFinished(this->line_01_startValue)))) {
            this->getEngine()->flushClockEvents(this, 1964277200, false);;
            this->line_01_scheduleNext();
        }
    }
    
    void line_01_end_bang() {}
    
    void line_01_target_set(const list& v) {
        this->line_01_target = jsCreateListCopy(v);
        this->line_01_pendingRamps->length = 0;
    
        if (v->length == 1) {
            this->line_01__time = this->line_01_time;
            this->line_01_time_set(0);
    
            if ((bool)(this->line_01__time))
                this->line_01_startRamp(v[0], this->line_01__time);
            else {
                this->line_01_output_set(v[0]);
                this->line_01_startValue = v[0];
                this->line_01_stop_bang();
            }
        } else if (v->length == 2) {
            this->line_01_time_set(0);
            this->line_01__time = (v[1] < 0 ? 0 : v[1]);
            this->line_01_startRamp(v[0], this->line_01__time);
        } else if (v->length == 3) {
            this->line_01_time_set(0);
            this->line_01_grain_set(v[2]);
            this->line_01__time = (v[1] < 0 ? 0 : v[1]);
            this->line_01_startRamp(v[0], this->line_01__time);
        } else {
            this->line_01_time_set(0);
            this->line_01_pendingRamps = jsCreateListCopy(v);
            this->line_01_startPendingRamp();
        }
    }
    
    void message_01_out_set(const list& v) {
        this->line_01_target_set(v);
    }
    
    void message_01_trigger_bang() {
        this->message_01_out_set(this->message_01_set);
    }
    
    void unpack_01_out1_set(number v) {
        this->unpack_01_out1 = v;
    
        {
            list converted = {v};
            this->message_01_set_set(converted);
        }
    
        this->message_01_trigger_bang();
    }
    
    void unpack_01_input_list_set(const list& v) {
        if (v->length > 7)
            this->unpack_01_out8_set(v[7]);
    
        if (v->length > 6)
            this->unpack_01_out7_set(v[6]);
    
        if (v->length > 5)
            this->unpack_01_out6_set(v[5]);
    
        if (v->length > 4)
            this->unpack_01_out5_set(v[4]);
    
        if (v->length > 3)
            this->unpack_01_out4_set(v[3]);
    
        if (v->length > 2)
            this->unpack_01_out3_set(v[2]);
    
        if (v->length > 1)
            this->unpack_01_out2_set(v[1]);
    
        if (v->length > 0)
            this->unpack_01_out1_set(v[0]);
    }
    
    void listrot_01_out1_set(const list& v) {
        this->unpack_01_input_list_set(v);
    }
    
    void listrot_01_input_bang() {
        list input = this->listrot_01_input;
        auto shift = this->listrot_01_shift;
        list tmp = jsCreateListCopy(input);
    
        if (tmp->length > 0) {
            if (shift > 0) {
                for (Index i = 0; i < shift; i++) {
                    tmp->unshift(tmp->pop());
                }
            } else {
                for (Index i = 0; i < -shift; i++) {
                    tmp->push(tmp->shift());
                }
            }
        }
    
        {
            this->listrot_01_out1_set(tmp);
            return;
        }
    }
    
    void button_01_output_bang() {
        this->listrot_01_input_bang();
    }
    
    void button_01_bangval_bang() {
        this->getEngine()->sendBangMessage(
            TAG("bangout"),
            TAG("rotating_clock_divider[1]/button_obj-57"),
            this->_currentTime
        );;
    
        this->button_01_output_bang();
    }
    
    void numberobj_01_output_set(number v) {
        this->listrot_01_shift_set(v);
        this->button_01_bangval_bang();
    }
    
    void numberobj_01_value_set(number v) {
        this->numberobj_01_value_setter(v);
        v = this->numberobj_01_value;
        number localvalue = v;
    
        if (this->numberobj_01_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("rotating_clock_divider[1]/number_obj-66"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_01_output_set(localvalue);
    }
    
    void eventinlet_02_out1_number_set(number v) {
        this->numberobj_01_value_set(v);
    }
    
    static number param_01_value_constrain(number v) {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    void p_01_in2_number_set(number v) {
        this->p_01->updateTime(this->_currentTime);
        this->p_01->eventinlet_01_out1_number_set(v);
    }
    
    void numberobj_01_value_bang() {
        number v = this->numberobj_01_value;
        number localvalue = v;
    
        if (this->numberobj_01_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("rotating_clock_divider[1]/number_obj-66"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_01_output_set(localvalue);
    }
    
    void listrot_01_input_set(const list& input) {
        this->listrot_01_input = jsCreateListCopy(input);
        auto shift = this->listrot_01_shift;
        list tmp = jsCreateListCopy(input);
    
        if (tmp->length > 0) {
            if (shift > 0) {
                for (Index i = 0; i < shift; i++) {
                    tmp->unshift(tmp->pop());
                }
            } else {
                for (Index i = 0; i < -shift; i++) {
                    tmp->push(tmp->shift());
                }
            }
        }
    
        {
            this->listrot_01_out1_set(tmp);
            return;
        }
    }
    
    void message_02_out_set(const list& v) {
        this->listrot_01_input_set(v);
    }
    
    void message_02_trigger_bang() {
        this->message_02_out_set(this->message_02_set);
    }
    
    void loadbang_01_output_bang() {
        this->message_02_trigger_bang();
    }
    
    void message_02_set_set(const list& v) {
        this->message_02_set = jsCreateListCopy(v);
    
        this->getEngine()->sendListMessage(
            TAG("listout"),
            TAG("rotating_clock_divider[1]/message_obj-53"),
            v,
            this->_currentTime
        );
    }
    
    void rate_tilde_03_perform(const Sample * phase, number multiplier, SampleValue * out1, Index n) {
        auto __rate_tilde_03_quant = this->rate_tilde_03_quant;
        auto __rate_tilde_03_currentPhase = this->rate_tilde_03_currentPhase;
        auto __rate_tilde_03_prev = this->rate_tilde_03_prev;
        auto __rate_tilde_03_diff = this->rate_tilde_03_diff;
        auto __rate_tilde_03_wantlock = this->rate_tilde_03_wantlock;
        auto __rate_tilde_03_invmult = this->rate_tilde_03_invmult;
        auto __rate_tilde_03_mult = this->rate_tilde_03_mult;
        Index i;
    
        for (i = 0; i < n; i++) {
            if (multiplier != __rate_tilde_03_mult && (bool)(!(bool)(rnbo_isnan(multiplier)))) {
                __rate_tilde_03_mult = multiplier;
                __rate_tilde_03_invmult = this->safediv(1.0, __rate_tilde_03_mult);
                __rate_tilde_03_wantlock = 1;
            }
    
            __rate_tilde_03_diff = phase[(Index)i] - __rate_tilde_03_prev;
    
            if (__rate_tilde_03_diff < -0.5) {
                __rate_tilde_03_diff += 1;
            } else if (__rate_tilde_03_diff > 0.5) {
                __rate_tilde_03_diff -= 1;
            }
    
            if ((bool)(__rate_tilde_03_wantlock)) {
                __rate_tilde_03_currentPhase = (phase[(Index)i] - this->quantize(phase[(Index)i], __rate_tilde_03_quant)) * __rate_tilde_03_invmult + this->quantize(phase[(Index)i], __rate_tilde_03_quant * __rate_tilde_03_mult);
                __rate_tilde_03_diff = 0;
                __rate_tilde_03_wantlock = 0;
            } else {
                __rate_tilde_03_currentPhase += __rate_tilde_03_diff * __rate_tilde_03_invmult;
            }
    
            if (__rate_tilde_03_currentPhase > 1.0 || __rate_tilde_03_currentPhase < -0.0) {
                __rate_tilde_03_currentPhase = __rate_tilde_03_currentPhase - rnbo_floor(__rate_tilde_03_currentPhase);
            }
    
            __rate_tilde_03_prev = phase[(Index)i];
            out1[(Index)i] = __rate_tilde_03_currentPhase;
            continue;
        }
    
        this->rate_tilde_03_mult = __rate_tilde_03_mult;
        this->rate_tilde_03_invmult = __rate_tilde_03_invmult;
        this->rate_tilde_03_wantlock = __rate_tilde_03_wantlock;
        this->rate_tilde_03_diff = __rate_tilde_03_diff;
        this->rate_tilde_03_prev = __rate_tilde_03_prev;
        this->rate_tilde_03_currentPhase = __rate_tilde_03_currentPhase;
    }
    
    void wrap_tilde_03_perform(const Sample * x, number low, number high, SampleValue * out1, Index n) {
        RNBO_UNUSED(high);
        RNBO_UNUSED(low);
        Index i;
    
        for (i = 0; i < n; i++) {
            number lo;
            number hi;
            lo = 0;
            hi = 1;
            number range = hi - lo;
    
            if (x[(Index)i] >= lo && x[(Index)i] < hi) {
                out1[(Index)i] = x[(Index)i];
                continue;
            }
    
            if (range <= 0.000000001) {
                out1[(Index)i] = lo;
                continue;
            }
    
            long numWraps = (long)(trunc((x[(Index)i] - lo) / range));
            numWraps = numWraps - ((x[(Index)i] < lo ? 1 : 0));
            number result = x[(Index)i] - range * numWraps;
    
            if (result >= hi) {
                out1[(Index)i] = result - range;
                continue;
            } else {
                out1[(Index)i] = result;
                continue;
            }
        }
    }
    
    void delta_tilde_03_perform(const Sample * x, SampleValue * out1, Index n) {
        auto __delta_tilde_03_prev = this->delta_tilde_03_prev;
        Index i;
    
        for (i = 0; i < n; i++) {
            number temp = (number)(x[(Index)i] - __delta_tilde_03_prev);
            __delta_tilde_03_prev = x[(Index)i];
            out1[(Index)i] = temp;
        }
    
        this->delta_tilde_03_prev = __delta_tilde_03_prev;
    }
    
    void dspexpr_06_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] < 0;//#map:_###_obj_###_:1
        }
    }
    
    void gen_04_perform(const Sample * in1, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            number counter_1 = 0;
            number counter_2 = 0;
            number counter_3 = 0;
            array<number, 3> result_1 = this->gen_04_counter_0_next(in1[(Index)i], 0, 0);
            counter_3 = result_1[2];
            counter_2 = result_1[1];
            counter_1 = result_1[0];
            number mod_4_2 = this->safemod(counter_1, 2);
            out1[(Index)i] = mod_4_2;
        }
    }
    
    void rate_tilde_04_perform(const Sample * phase, number multiplier, SampleValue * out1, Index n) {
        auto __rate_tilde_04_quant = this->rate_tilde_04_quant;
        auto __rate_tilde_04_currentPhase = this->rate_tilde_04_currentPhase;
        auto __rate_tilde_04_prev = this->rate_tilde_04_prev;
        auto __rate_tilde_04_diff = this->rate_tilde_04_diff;
        auto __rate_tilde_04_wantlock = this->rate_tilde_04_wantlock;
        auto __rate_tilde_04_invmult = this->rate_tilde_04_invmult;
        auto __rate_tilde_04_mult = this->rate_tilde_04_mult;
        Index i;
    
        for (i = 0; i < n; i++) {
            if (multiplier != __rate_tilde_04_mult && (bool)(!(bool)(rnbo_isnan(multiplier)))) {
                __rate_tilde_04_mult = multiplier;
                __rate_tilde_04_invmult = this->safediv(1.0, __rate_tilde_04_mult);
                __rate_tilde_04_wantlock = 1;
            }
    
            __rate_tilde_04_diff = phase[(Index)i] - __rate_tilde_04_prev;
    
            if (__rate_tilde_04_diff < -0.5) {
                __rate_tilde_04_diff += 1;
            } else if (__rate_tilde_04_diff > 0.5) {
                __rate_tilde_04_diff -= 1;
            }
    
            if ((bool)(__rate_tilde_04_wantlock)) {
                __rate_tilde_04_currentPhase = (phase[(Index)i] - this->quantize(phase[(Index)i], __rate_tilde_04_quant)) * __rate_tilde_04_invmult + this->quantize(phase[(Index)i], __rate_tilde_04_quant * __rate_tilde_04_mult);
                __rate_tilde_04_diff = 0;
                __rate_tilde_04_wantlock = 0;
            } else {
                __rate_tilde_04_currentPhase += __rate_tilde_04_diff * __rate_tilde_04_invmult;
            }
    
            if (__rate_tilde_04_currentPhase > 1.0 || __rate_tilde_04_currentPhase < -0.0) {
                __rate_tilde_04_currentPhase = __rate_tilde_04_currentPhase - rnbo_floor(__rate_tilde_04_currentPhase);
            }
    
            __rate_tilde_04_prev = phase[(Index)i];
            out1[(Index)i] = __rate_tilde_04_currentPhase;
            continue;
        }
    
        this->rate_tilde_04_mult = __rate_tilde_04_mult;
        this->rate_tilde_04_invmult = __rate_tilde_04_invmult;
        this->rate_tilde_04_wantlock = __rate_tilde_04_wantlock;
        this->rate_tilde_04_diff = __rate_tilde_04_diff;
        this->rate_tilde_04_prev = __rate_tilde_04_prev;
        this->rate_tilde_04_currentPhase = __rate_tilde_04_currentPhase;
    }
    
    void wrap_tilde_04_perform(const Sample * x, number low, number high, SampleValue * out1, Index n) {
        RNBO_UNUSED(high);
        RNBO_UNUSED(low);
        Index i;
    
        for (i = 0; i < n; i++) {
            number lo;
            number hi;
            lo = 0;
            hi = 1;
            number range = hi - lo;
    
            if (x[(Index)i] >= lo && x[(Index)i] < hi) {
                out1[(Index)i] = x[(Index)i];
                continue;
            }
    
            if (range <= 0.000000001) {
                out1[(Index)i] = lo;
                continue;
            }
    
            long numWraps = (long)(trunc((x[(Index)i] - lo) / range));
            numWraps = numWraps - ((x[(Index)i] < lo ? 1 : 0));
            number result = x[(Index)i] - range * numWraps;
    
            if (result >= hi) {
                out1[(Index)i] = result - range;
                continue;
            } else {
                out1[(Index)i] = result;
                continue;
            }
        }
    }
    
    void delta_tilde_04_perform(const Sample * x, SampleValue * out1, Index n) {
        auto __delta_tilde_04_prev = this->delta_tilde_04_prev;
        Index i;
    
        for (i = 0; i < n; i++) {
            number temp = (number)(x[(Index)i] - __delta_tilde_04_prev);
            __delta_tilde_04_prev = x[(Index)i];
            out1[(Index)i] = temp;
        }
    
        this->delta_tilde_04_prev = __delta_tilde_04_prev;
    }
    
    void dspexpr_07_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] < 0;//#map:_###_obj_###_:1
        }
    }
    
    void gen_05_perform(const Sample * in1, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            number counter_1 = 0;
            number counter_2 = 0;
            number counter_3 = 0;
            array<number, 3> result_1 = this->gen_05_counter_0_next(in1[(Index)i], 0, 0);
            counter_3 = result_1[2];
            counter_2 = result_1[1];
            counter_1 = result_1[0];
            number mod_4_2 = this->safemod(counter_1, 2);
            out1[(Index)i] = mod_4_2;
        }
    }
    
    void rate_tilde_02_perform(const Sample * phase, number multiplier, SampleValue * out1, Index n) {
        auto __rate_tilde_02_quant = this->rate_tilde_02_quant;
        auto __rate_tilde_02_currentPhase = this->rate_tilde_02_currentPhase;
        auto __rate_tilde_02_prev = this->rate_tilde_02_prev;
        auto __rate_tilde_02_diff = this->rate_tilde_02_diff;
        auto __rate_tilde_02_wantlock = this->rate_tilde_02_wantlock;
        auto __rate_tilde_02_invmult = this->rate_tilde_02_invmult;
        auto __rate_tilde_02_mult = this->rate_tilde_02_mult;
        Index i;
    
        for (i = 0; i < n; i++) {
            if (multiplier != __rate_tilde_02_mult && (bool)(!(bool)(rnbo_isnan(multiplier)))) {
                __rate_tilde_02_mult = multiplier;
                __rate_tilde_02_invmult = this->safediv(1.0, __rate_tilde_02_mult);
                __rate_tilde_02_wantlock = 1;
            }
    
            __rate_tilde_02_diff = phase[(Index)i] - __rate_tilde_02_prev;
    
            if (__rate_tilde_02_diff < -0.5) {
                __rate_tilde_02_diff += 1;
            } else if (__rate_tilde_02_diff > 0.5) {
                __rate_tilde_02_diff -= 1;
            }
    
            if ((bool)(__rate_tilde_02_wantlock)) {
                __rate_tilde_02_currentPhase = (phase[(Index)i] - this->quantize(phase[(Index)i], __rate_tilde_02_quant)) * __rate_tilde_02_invmult + this->quantize(phase[(Index)i], __rate_tilde_02_quant * __rate_tilde_02_mult);
                __rate_tilde_02_diff = 0;
                __rate_tilde_02_wantlock = 0;
            } else {
                __rate_tilde_02_currentPhase += __rate_tilde_02_diff * __rate_tilde_02_invmult;
            }
    
            if (__rate_tilde_02_currentPhase > 1.0 || __rate_tilde_02_currentPhase < -0.0) {
                __rate_tilde_02_currentPhase = __rate_tilde_02_currentPhase - rnbo_floor(__rate_tilde_02_currentPhase);
            }
    
            __rate_tilde_02_prev = phase[(Index)i];
            out1[(Index)i] = __rate_tilde_02_currentPhase;
            continue;
        }
    
        this->rate_tilde_02_mult = __rate_tilde_02_mult;
        this->rate_tilde_02_invmult = __rate_tilde_02_invmult;
        this->rate_tilde_02_wantlock = __rate_tilde_02_wantlock;
        this->rate_tilde_02_diff = __rate_tilde_02_diff;
        this->rate_tilde_02_prev = __rate_tilde_02_prev;
        this->rate_tilde_02_currentPhase = __rate_tilde_02_currentPhase;
    }
    
    void wrap_tilde_02_perform(const Sample * x, number low, number high, SampleValue * out1, Index n) {
        RNBO_UNUSED(high);
        RNBO_UNUSED(low);
        Index i;
    
        for (i = 0; i < n; i++) {
            number lo;
            number hi;
            lo = 0;
            hi = 1;
            number range = hi - lo;
    
            if (x[(Index)i] >= lo && x[(Index)i] < hi) {
                out1[(Index)i] = x[(Index)i];
                continue;
            }
    
            if (range <= 0.000000001) {
                out1[(Index)i] = lo;
                continue;
            }
    
            long numWraps = (long)(trunc((x[(Index)i] - lo) / range));
            numWraps = numWraps - ((x[(Index)i] < lo ? 1 : 0));
            number result = x[(Index)i] - range * numWraps;
    
            if (result >= hi) {
                out1[(Index)i] = result - range;
                continue;
            } else {
                out1[(Index)i] = result;
                continue;
            }
        }
    }
    
    void delta_tilde_02_perform(const Sample * x, SampleValue * out1, Index n) {
        auto __delta_tilde_02_prev = this->delta_tilde_02_prev;
        Index i;
    
        for (i = 0; i < n; i++) {
            number temp = (number)(x[(Index)i] - __delta_tilde_02_prev);
            __delta_tilde_02_prev = x[(Index)i];
            out1[(Index)i] = temp;
        }
    
        this->delta_tilde_02_prev = __delta_tilde_02_prev;
    }
    
    void dspexpr_05_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] < 0;//#map:_###_obj_###_:1
        }
    }
    
    void gen_03_perform(const Sample * in1, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            number counter_1 = 0;
            number counter_2 = 0;
            number counter_3 = 0;
            array<number, 3> result_1 = this->gen_03_counter_0_next(in1[(Index)i], 0, 0);
            counter_3 = result_1[2];
            counter_2 = result_1[1];
            counter_1 = result_1[0];
            number mod_4_2 = this->safemod(counter_1, 2);
            out1[(Index)i] = mod_4_2;
        }
    }
    
    void rate_tilde_01_perform(const Sample * phase, number multiplier, SampleValue * out1, Index n) {
        auto __rate_tilde_01_quant = this->rate_tilde_01_quant;
        auto __rate_tilde_01_currentPhase = this->rate_tilde_01_currentPhase;
        auto __rate_tilde_01_prev = this->rate_tilde_01_prev;
        auto __rate_tilde_01_diff = this->rate_tilde_01_diff;
        auto __rate_tilde_01_wantlock = this->rate_tilde_01_wantlock;
        auto __rate_tilde_01_invmult = this->rate_tilde_01_invmult;
        auto __rate_tilde_01_mult = this->rate_tilde_01_mult;
        Index i;
    
        for (i = 0; i < n; i++) {
            if (multiplier != __rate_tilde_01_mult && (bool)(!(bool)(rnbo_isnan(multiplier)))) {
                __rate_tilde_01_mult = multiplier;
                __rate_tilde_01_invmult = this->safediv(1.0, __rate_tilde_01_mult);
                __rate_tilde_01_wantlock = 1;
            }
    
            __rate_tilde_01_diff = phase[(Index)i] - __rate_tilde_01_prev;
    
            if (__rate_tilde_01_diff < -0.5) {
                __rate_tilde_01_diff += 1;
            } else if (__rate_tilde_01_diff > 0.5) {
                __rate_tilde_01_diff -= 1;
            }
    
            if ((bool)(__rate_tilde_01_wantlock)) {
                __rate_tilde_01_currentPhase = (phase[(Index)i] - this->quantize(phase[(Index)i], __rate_tilde_01_quant)) * __rate_tilde_01_invmult + this->quantize(phase[(Index)i], __rate_tilde_01_quant * __rate_tilde_01_mult);
                __rate_tilde_01_diff = 0;
                __rate_tilde_01_wantlock = 0;
            } else {
                __rate_tilde_01_currentPhase += __rate_tilde_01_diff * __rate_tilde_01_invmult;
            }
    
            if (__rate_tilde_01_currentPhase > 1.0 || __rate_tilde_01_currentPhase < -0.0) {
                __rate_tilde_01_currentPhase = __rate_tilde_01_currentPhase - rnbo_floor(__rate_tilde_01_currentPhase);
            }
    
            __rate_tilde_01_prev = phase[(Index)i];
            out1[(Index)i] = __rate_tilde_01_currentPhase;
            continue;
        }
    
        this->rate_tilde_01_mult = __rate_tilde_01_mult;
        this->rate_tilde_01_invmult = __rate_tilde_01_invmult;
        this->rate_tilde_01_wantlock = __rate_tilde_01_wantlock;
        this->rate_tilde_01_diff = __rate_tilde_01_diff;
        this->rate_tilde_01_prev = __rate_tilde_01_prev;
        this->rate_tilde_01_currentPhase = __rate_tilde_01_currentPhase;
    }
    
    void wrap_tilde_01_perform(const Sample * x, number low, number high, SampleValue * out1, Index n) {
        RNBO_UNUSED(high);
        RNBO_UNUSED(low);
        Index i;
    
        for (i = 0; i < n; i++) {
            number lo;
            number hi;
            lo = 0;
            hi = 1;
            number range = hi - lo;
    
            if (x[(Index)i] >= lo && x[(Index)i] < hi) {
                out1[(Index)i] = x[(Index)i];
                continue;
            }
    
            if (range <= 0.000000001) {
                out1[(Index)i] = lo;
                continue;
            }
    
            long numWraps = (long)(trunc((x[(Index)i] - lo) / range));
            numWraps = numWraps - ((x[(Index)i] < lo ? 1 : 0));
            number result = x[(Index)i] - range * numWraps;
    
            if (result >= hi) {
                out1[(Index)i] = result - range;
                continue;
            } else {
                out1[(Index)i] = result;
                continue;
            }
        }
    }
    
    void delta_tilde_01_perform(const Sample * x, SampleValue * out1, Index n) {
        auto __delta_tilde_01_prev = this->delta_tilde_01_prev;
        Index i;
    
        for (i = 0; i < n; i++) {
            number temp = (number)(x[(Index)i] - __delta_tilde_01_prev);
            __delta_tilde_01_prev = x[(Index)i];
            out1[(Index)i] = temp;
        }
    
        this->delta_tilde_01_prev = __delta_tilde_01_prev;
    }
    
    void dspexpr_04_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] < 0;//#map:_###_obj_###_:1
        }
    }
    
    void gen_02_perform(const Sample * in1, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            number counter_1 = 0;
            number counter_2 = 0;
            number counter_3 = 0;
            array<number, 3> result_1 = this->gen_02_counter_0_next(in1[(Index)i], 0, 0);
            counter_3 = result_1[2];
            counter_2 = result_1[1];
            counter_1 = result_1[0];
            number mod_4_2 = this->safemod(counter_1, 2);
            out1[(Index)i] = mod_4_2;
        }
    }
    
    void p_01_perform(const SampleValue * in1, SampleValue * out3, Index n) {
        // subpatcher: probability_skip
        ConstSampleArray<1> ins = {in1};
    
        SampleArray<1> outs = {out3};
        this->p_01->process(ins, 1, outs, 1, n);
    }
    
    void gen_01_perform(const Sample * in1, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            number counter_1 = 0;
            number counter_2 = 0;
            number counter_3 = 0;
            array<number, 3> result_1 = this->gen_01_counter_0_next(in1[(Index)i], 0, 0);
            counter_3 = result_1[2];
            counter_2 = result_1[1];
            counter_1 = result_1[0];
            number mod_4_2 = this->safemod(counter_1, 2);
            out1[(Index)i] = mod_4_2;
        }
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void numberobj_01_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_01_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_01_value = localvalue;
    }
    
    array<number, 3> gen_01_counter_0_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        RNBO_UNUSED(reset);
        number carry_flag = 0;
    
        {
            this->gen_01_counter_0_count += a;
        }
    
        return {this->gen_01_counter_0_count, carry_flag, this->gen_01_counter_0_carry};
    }
    
    void gen_01_counter_0_init() {
        this->gen_01_counter_0_count = 0;
    }
    
    void gen_01_counter_0_reset() {
        this->gen_01_counter_0_carry = 0;
        this->gen_01_counter_0_count = 0;
    }
    
    array<number, 3> gen_02_counter_0_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        RNBO_UNUSED(reset);
        number carry_flag = 0;
    
        {
            this->gen_02_counter_0_count += a;
        }
    
        return {this->gen_02_counter_0_count, carry_flag, this->gen_02_counter_0_carry};
    }
    
    void gen_02_counter_0_init() {
        this->gen_02_counter_0_count = 0;
    }
    
    void gen_02_counter_0_reset() {
        this->gen_02_counter_0_carry = 0;
        this->gen_02_counter_0_count = 0;
    }
    
    void rate_tilde_01_reset() {
        this->rate_tilde_01_currentPhase = 0;
        this->rate_tilde_01_diff = 0;
        this->rate_tilde_01_prev = 0;
        this->rate_tilde_01_mult = 1;
        this->rate_tilde_01_invmult = 1;
        this->rate_tilde_01_wantlock = 1;
        this->rate_tilde_01_quant = 1;
    }
    
    void rate_tilde_01_dspsetup(bool force) {
        if ((bool)(this->rate_tilde_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->rate_tilde_01_reset();
        this->rate_tilde_01_setupDone = true;
    }
    
    void delta_tilde_01_reset() {
        this->delta_tilde_01_prev = 0;
    }
    
    void delta_tilde_01_dspsetup(bool force) {
        if ((bool)(this->delta_tilde_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->delta_tilde_01_reset();
        this->delta_tilde_01_setupDone = true;
    }
    
    void numberobj_01_init() {
        this->numberobj_01_currentFormat = 6;
    
        this->getEngine()->sendNumMessage(
            TAG("setup"),
            TAG("rotating_clock_divider[1]/number_obj-66"),
            1,
            this->_currentTime
        );
    }
    
    void numberobj_01_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_01_value;
    }
    
    void numberobj_01_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_01_value_set(preset["value"]);
    }
    
    number line_01_valueAtTime(number time) {
        return this->line_01_startValue + this->line_01_slope * (time - this->line_01_startTime);
    }
    
    void line_01_scheduleNext() {
        auto currentTime = this->currenttime();
        number nextTime = currentTime + this->line_01_grain;
        number nextValue;
    
        if (nextTime - this->line_01_startTime >= this->line_01__time || this->line_01_grain == 0) {
            nextTime = this->line_01_startTime + this->line_01__time;
            nextValue = this->line_01_currentTarget;
        } else {
            nextValue = this->line_01_valueAtTime(nextTime);
        }
    
        this->getEngine()->scheduleClockEventWithValue(this, 1964277200, nextTime - currentTime + this->_currentTime, nextValue);;
    }
    
    void line_01_startRamp(number target, MillisecondTime time) {
        auto currentTime = this->currenttime();
        this->line_01_startValue = this->line_01_valueAtTime(currentTime);
        this->line_01_startTime = currentTime;
        this->line_01_currentTarget = target;
        this->getEngine()->flushClockEvents(this, 1964277200, false);;
        number rise = target - this->line_01_startValue;
        this->line_01_slope = rise / time;
        this->line_01_scheduleNext();
    }
    
    bool line_01_isFinished(number value) {
        return value == this->line_01_currentTarget && this->currenttime() - this->line_01_startTime >= this->line_01__time;
    }
    
    void line_01_startPendingRamp() {
        if (this->line_01_pendingRamps->length < 2) {
            this->line_01_pendingRamps->length = 0;
            this->line_01__time = 0;
            this->line_01_time_set(0);
            this->line_01_end_bang();
            return;
        }
    
        if (this->line_01_pendingRamps->length > 1) {
            number target = this->line_01_pendingRamps->shift();
            this->line_01__time = this->line_01_pendingRamps->shift();
            this->line_01__time = (this->line_01__time < 0 ? 0 : this->line_01__time);
            this->line_01_startRamp(target, this->line_01__time);
        }
    }
    
    void message_01_init() {
        this->message_01_set_set({3});
    }
    
    void message_02_init() {
        this->message_02_set_set({1, 2, 3, 4, 5, 6, 7, 8});
    }
    
    void param_01_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_01_value;
    }
    
    void param_01_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_01_value_set(preset["value"]);
    }
    
    array<number, 3> gen_03_counter_0_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        RNBO_UNUSED(reset);
        number carry_flag = 0;
    
        {
            this->gen_03_counter_0_count += a;
        }
    
        return {this->gen_03_counter_0_count, carry_flag, this->gen_03_counter_0_carry};
    }
    
    void gen_03_counter_0_init() {
        this->gen_03_counter_0_count = 0;
    }
    
    void gen_03_counter_0_reset() {
        this->gen_03_counter_0_carry = 0;
        this->gen_03_counter_0_count = 0;
    }
    
    void rate_tilde_02_reset() {
        this->rate_tilde_02_currentPhase = 0;
        this->rate_tilde_02_diff = 0;
        this->rate_tilde_02_prev = 0;
        this->rate_tilde_02_mult = 1;
        this->rate_tilde_02_invmult = 1;
        this->rate_tilde_02_wantlock = 1;
        this->rate_tilde_02_quant = 1;
    }
    
    void rate_tilde_02_dspsetup(bool force) {
        if ((bool)(this->rate_tilde_02_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->rate_tilde_02_reset();
        this->rate_tilde_02_setupDone = true;
    }
    
    void delta_tilde_02_reset() {
        this->delta_tilde_02_prev = 0;
    }
    
    void delta_tilde_02_dspsetup(bool force) {
        if ((bool)(this->delta_tilde_02_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->delta_tilde_02_reset();
        this->delta_tilde_02_setupDone = true;
    }
    
    number line_02_valueAtTime(number time) {
        return this->line_02_startValue + this->line_02_slope * (time - this->line_02_startTime);
    }
    
    void line_02_scheduleNext() {
        auto currentTime = this->currenttime();
        number nextTime = currentTime + this->line_02_grain;
        number nextValue;
    
        if (nextTime - this->line_02_startTime >= this->line_02__time || this->line_02_grain == 0) {
            nextTime = this->line_02_startTime + this->line_02__time;
            nextValue = this->line_02_currentTarget;
        } else {
            nextValue = this->line_02_valueAtTime(nextTime);
        }
    
        this->getEngine()->scheduleClockEventWithValue(this, 1592269969, nextTime - currentTime + this->_currentTime, nextValue);;
    }
    
    void line_02_startRamp(number target, MillisecondTime time) {
        auto currentTime = this->currenttime();
        this->line_02_startValue = this->line_02_valueAtTime(currentTime);
        this->line_02_startTime = currentTime;
        this->line_02_currentTarget = target;
        this->getEngine()->flushClockEvents(this, 1592269969, false);;
        number rise = target - this->line_02_startValue;
        this->line_02_slope = rise / time;
        this->line_02_scheduleNext();
    }
    
    bool line_02_isFinished(number value) {
        return value == this->line_02_currentTarget && this->currenttime() - this->line_02_startTime >= this->line_02__time;
    }
    
    void line_02_startPendingRamp() {
        if (this->line_02_pendingRamps->length < 2) {
            this->line_02_pendingRamps->length = 0;
            this->line_02__time = 0;
            this->line_02_time_set(0);
            this->line_02_end_bang();
            return;
        }
    
        if (this->line_02_pendingRamps->length > 1) {
            number target = this->line_02_pendingRamps->shift();
            this->line_02__time = this->line_02_pendingRamps->shift();
            this->line_02__time = (this->line_02__time < 0 ? 0 : this->line_02__time);
            this->line_02_startRamp(target, this->line_02__time);
        }
    }
    
    void message_03_init() {
        this->message_03_set_set({4});
    }
    
    void rate_tilde_03_reset() {
        this->rate_tilde_03_currentPhase = 0;
        this->rate_tilde_03_diff = 0;
        this->rate_tilde_03_prev = 0;
        this->rate_tilde_03_mult = 1;
        this->rate_tilde_03_invmult = 1;
        this->rate_tilde_03_wantlock = 1;
        this->rate_tilde_03_quant = 1;
    }
    
    void rate_tilde_03_dspsetup(bool force) {
        if ((bool)(this->rate_tilde_03_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->rate_tilde_03_reset();
        this->rate_tilde_03_setupDone = true;
    }
    
    void delta_tilde_03_reset() {
        this->delta_tilde_03_prev = 0;
    }
    
    void delta_tilde_03_dspsetup(bool force) {
        if ((bool)(this->delta_tilde_03_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->delta_tilde_03_reset();
        this->delta_tilde_03_setupDone = true;
    }
    
    array<number, 3> gen_04_counter_0_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        RNBO_UNUSED(reset);
        number carry_flag = 0;
    
        {
            this->gen_04_counter_0_count += a;
        }
    
        return {this->gen_04_counter_0_count, carry_flag, this->gen_04_counter_0_carry};
    }
    
    void gen_04_counter_0_init() {
        this->gen_04_counter_0_count = 0;
    }
    
    void gen_04_counter_0_reset() {
        this->gen_04_counter_0_carry = 0;
        this->gen_04_counter_0_count = 0;
    }
    
    number line_03_valueAtTime(number time) {
        return this->line_03_startValue + this->line_03_slope * (time - this->line_03_startTime);
    }
    
    void line_03_scheduleNext() {
        auto currentTime = this->currenttime();
        number nextTime = currentTime + this->line_03_grain;
        number nextValue;
    
        if (nextTime - this->line_03_startTime >= this->line_03__time || this->line_03_grain == 0) {
            nextTime = this->line_03_startTime + this->line_03__time;
            nextValue = this->line_03_currentTarget;
        } else {
            nextValue = this->line_03_valueAtTime(nextTime);
        }
    
        this->getEngine()->scheduleClockEventWithValue(this, 1220262738, nextTime - currentTime + this->_currentTime, nextValue);;
    }
    
    void line_03_startRamp(number target, MillisecondTime time) {
        auto currentTime = this->currenttime();
        this->line_03_startValue = this->line_03_valueAtTime(currentTime);
        this->line_03_startTime = currentTime;
        this->line_03_currentTarget = target;
        this->getEngine()->flushClockEvents(this, 1220262738, false);;
        number rise = target - this->line_03_startValue;
        this->line_03_slope = rise / time;
        this->line_03_scheduleNext();
    }
    
    bool line_03_isFinished(number value) {
        return value == this->line_03_currentTarget && this->currenttime() - this->line_03_startTime >= this->line_03__time;
    }
    
    void line_03_startPendingRamp() {
        if (this->line_03_pendingRamps->length < 2) {
            this->line_03_pendingRamps->length = 0;
            this->line_03__time = 0;
            this->line_03_time_set(0);
            this->line_03_end_bang();
            return;
        }
    
        if (this->line_03_pendingRamps->length > 1) {
            number target = this->line_03_pendingRamps->shift();
            this->line_03__time = this->line_03_pendingRamps->shift();
            this->line_03__time = (this->line_03__time < 0 ? 0 : this->line_03__time);
            this->line_03_startRamp(target, this->line_03__time);
        }
    }
    
    void message_04_init() {
        this->message_04_set_set({5});
    }
    
    array<number, 3> gen_05_counter_0_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        RNBO_UNUSED(reset);
        number carry_flag = 0;
    
        {
            this->gen_05_counter_0_count += a;
        }
    
        return {this->gen_05_counter_0_count, carry_flag, this->gen_05_counter_0_carry};
    }
    
    void gen_05_counter_0_init() {
        this->gen_05_counter_0_count = 0;
    }
    
    void gen_05_counter_0_reset() {
        this->gen_05_counter_0_carry = 0;
        this->gen_05_counter_0_count = 0;
    }
    
    void rate_tilde_04_reset() {
        this->rate_tilde_04_currentPhase = 0;
        this->rate_tilde_04_diff = 0;
        this->rate_tilde_04_prev = 0;
        this->rate_tilde_04_mult = 1;
        this->rate_tilde_04_invmult = 1;
        this->rate_tilde_04_wantlock = 1;
        this->rate_tilde_04_quant = 1;
    }
    
    void rate_tilde_04_dspsetup(bool force) {
        if ((bool)(this->rate_tilde_04_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->rate_tilde_04_reset();
        this->rate_tilde_04_setupDone = true;
    }
    
    void delta_tilde_04_reset() {
        this->delta_tilde_04_prev = 0;
    }
    
    void delta_tilde_04_dspsetup(bool force) {
        if ((bool)(this->delta_tilde_04_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->delta_tilde_04_reset();
        this->delta_tilde_04_setupDone = true;
    }
    
    number line_04_valueAtTime(number time) {
        return this->line_04_startValue + this->line_04_slope * (time - this->line_04_startTime);
    }
    
    void line_04_scheduleNext() {
        auto currentTime = this->currenttime();
        number nextTime = currentTime + this->line_04_grain;
        number nextValue;
    
        if (nextTime - this->line_04_startTime >= this->line_04__time || this->line_04_grain == 0) {
            nextTime = this->line_04_startTime + this->line_04__time;
            nextValue = this->line_04_currentTarget;
        } else {
            nextValue = this->line_04_valueAtTime(nextTime);
        }
    
        this->getEngine()->scheduleClockEventWithValue(this, 848255507, nextTime - currentTime + this->_currentTime, nextValue);;
    }
    
    void line_04_startRamp(number target, MillisecondTime time) {
        auto currentTime = this->currenttime();
        this->line_04_startValue = this->line_04_valueAtTime(currentTime);
        this->line_04_startTime = currentTime;
        this->line_04_currentTarget = target;
        this->getEngine()->flushClockEvents(this, 848255507, false);;
        number rise = target - this->line_04_startValue;
        this->line_04_slope = rise / time;
        this->line_04_scheduleNext();
    }
    
    bool line_04_isFinished(number value) {
        return value == this->line_04_currentTarget && this->currenttime() - this->line_04_startTime >= this->line_04__time;
    }
    
    void line_04_startPendingRamp() {
        if (this->line_04_pendingRamps->length < 2) {
            this->line_04_pendingRamps->length = 0;
            this->line_04__time = 0;
            this->line_04_time_set(0);
            this->line_04_end_bang();
            return;
        }
    
        if (this->line_04_pendingRamps->length > 1) {
            number target = this->line_04_pendingRamps->shift();
            this->line_04__time = this->line_04_pendingRamps->shift();
            this->line_04__time = (this->line_04__time < 0 ? 0 : this->line_04__time);
            this->line_04_startRamp(target, this->line_04__time);
        }
    }
    
    void message_05_init() {
        this->message_05_set_set({6});
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        gen_01_in1 = 0;
        p_01_target = 0;
        gen_02_in1 = 0;
        rate_tilde_01_phase = 0;
        rate_tilde_01_multiplier = 1;
        dspexpr_04_in1 = 0;
        dspexpr_04_in2 = 0;
        delta_tilde_01_x = 0;
        wrap_tilde_01_x = 0;
        wrap_tilde_01_low = 0;
        wrap_tilde_01_high = 1;
        numberobj_01_value = 0;
        numberobj_01_value_setter(numberobj_01_value);
        line_01_time = 0;
        line_01_grain = 100;
        line_01_output = 0;
        unpack_01_out1 = 0;
        unpack_01_out2 = 0;
        unpack_01_out3 = 0;
        unpack_01_out4 = 0;
        unpack_01_out5 = 0;
        unpack_01_out6 = 0;
        unpack_01_out7 = 0;
        unpack_01_out8 = 0;
        listrot_01_shift = 0;
        param_01_value = 0;
        gen_03_in1 = 0;
        rate_tilde_02_phase = 0;
        rate_tilde_02_multiplier = 1;
        dspexpr_05_in1 = 0;
        dspexpr_05_in2 = 0;
        delta_tilde_02_x = 0;
        wrap_tilde_02_x = 0;
        wrap_tilde_02_low = 0;
        wrap_tilde_02_high = 1;
        line_02_time = 0;
        line_02_grain = 100;
        line_02_output = 0;
        rate_tilde_03_phase = 0;
        rate_tilde_03_multiplier = 1;
        dspexpr_06_in1 = 0;
        dspexpr_06_in2 = 0;
        delta_tilde_03_x = 0;
        wrap_tilde_03_x = 0;
        wrap_tilde_03_low = 0;
        wrap_tilde_03_high = 1;
        gen_04_in1 = 0;
        line_03_time = 0;
        line_03_grain = 100;
        line_03_output = 0;
        gen_05_in1 = 0;
        rate_tilde_04_phase = 0;
        rate_tilde_04_multiplier = 1;
        dspexpr_07_in1 = 0;
        dspexpr_07_in2 = 0;
        delta_tilde_04_x = 0;
        wrap_tilde_04_x = 0;
        wrap_tilde_04_low = 0;
        wrap_tilde_04_high = 1;
        line_04_time = 0;
        line_04_grain = 100;
        line_04_output = 0;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        gen_01_counter_0_carry = 0;
        gen_01_counter_0_count = 0;
        gen_02_counter_0_carry = 0;
        gen_02_counter_0_count = 0;
        rate_tilde_01_currentPhase = 0;
        rate_tilde_01_diff = 0;
        rate_tilde_01_prev = 0;
        rate_tilde_01_mult = 1;
        rate_tilde_01_invmult = 1;
        rate_tilde_01_wantlock = 1;
        rate_tilde_01_quant = 1;
        rate_tilde_01_setupDone = false;
        delta_tilde_01_prev = 0;
        delta_tilde_01_setupDone = false;
        numberobj_01_currentFormat = 6;
        numberobj_01_lastValue = 0;
        line_01_startTime = 0;
        line_01_startValue = 0;
        line_01_currentTarget = 0;
        line_01_slope = 0;
        line_01__time = 0;
        param_01_lastValue = 0;
        gen_03_counter_0_carry = 0;
        gen_03_counter_0_count = 0;
        rate_tilde_02_currentPhase = 0;
        rate_tilde_02_diff = 0;
        rate_tilde_02_prev = 0;
        rate_tilde_02_mult = 1;
        rate_tilde_02_invmult = 1;
        rate_tilde_02_wantlock = 1;
        rate_tilde_02_quant = 1;
        rate_tilde_02_setupDone = false;
        delta_tilde_02_prev = 0;
        delta_tilde_02_setupDone = false;
        line_02_startTime = 0;
        line_02_startValue = 0;
        line_02_currentTarget = 0;
        line_02_slope = 0;
        line_02__time = 0;
        rate_tilde_03_currentPhase = 0;
        rate_tilde_03_diff = 0;
        rate_tilde_03_prev = 0;
        rate_tilde_03_mult = 1;
        rate_tilde_03_invmult = 1;
        rate_tilde_03_wantlock = 1;
        rate_tilde_03_quant = 1;
        rate_tilde_03_setupDone = false;
        delta_tilde_03_prev = 0;
        delta_tilde_03_setupDone = false;
        gen_04_counter_0_carry = 0;
        gen_04_counter_0_count = 0;
        line_03_startTime = 0;
        line_03_startValue = 0;
        line_03_currentTarget = 0;
        line_03_slope = 0;
        line_03__time = 0;
        gen_05_counter_0_carry = 0;
        gen_05_counter_0_count = 0;
        rate_tilde_04_currentPhase = 0;
        rate_tilde_04_diff = 0;
        rate_tilde_04_prev = 0;
        rate_tilde_04_mult = 1;
        rate_tilde_04_invmult = 1;
        rate_tilde_04_wantlock = 1;
        rate_tilde_04_quant = 1;
        rate_tilde_04_setupDone = false;
        delta_tilde_04_prev = 0;
        delta_tilde_04_setupDone = false;
        line_04_startTime = 0;
        line_04_startValue = 0;
        line_04_currentTarget = 0;
        line_04_slope = 0;
        line_04__time = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number gen_01_in1;
        number p_01_target;
        number gen_02_in1;
        number rate_tilde_01_phase;
        number rate_tilde_01_multiplier;
        number dspexpr_04_in1;
        number dspexpr_04_in2;
        number delta_tilde_01_x;
        number wrap_tilde_01_x;
        number wrap_tilde_01_low;
        number wrap_tilde_01_high;
        number numberobj_01_value;
        list line_01_target;
        number line_01_time;
        number line_01_grain;
        number line_01_output;
        list message_01_set;
        number unpack_01_out1;
        number unpack_01_out2;
        number unpack_01_out3;
        number unpack_01_out4;
        number unpack_01_out5;
        number unpack_01_out6;
        number unpack_01_out7;
        number unpack_01_out8;
        list listrot_01_input;
        number listrot_01_shift;
        list message_02_set;
        number param_01_value;
        number gen_03_in1;
        number rate_tilde_02_phase;
        number rate_tilde_02_multiplier;
        number dspexpr_05_in1;
        number dspexpr_05_in2;
        number delta_tilde_02_x;
        number wrap_tilde_02_x;
        number wrap_tilde_02_low;
        number wrap_tilde_02_high;
        list line_02_target;
        number line_02_time;
        number line_02_grain;
        number line_02_output;
        list message_03_set;
        number rate_tilde_03_phase;
        number rate_tilde_03_multiplier;
        number dspexpr_06_in1;
        number dspexpr_06_in2;
        number delta_tilde_03_x;
        number wrap_tilde_03_x;
        number wrap_tilde_03_low;
        number wrap_tilde_03_high;
        number gen_04_in1;
        list line_03_target;
        number line_03_time;
        number line_03_grain;
        number line_03_output;
        list message_04_set;
        number gen_05_in1;
        number rate_tilde_04_phase;
        number rate_tilde_04_multiplier;
        number dspexpr_07_in1;
        number dspexpr_07_in2;
        number delta_tilde_04_x;
        number wrap_tilde_04_x;
        number wrap_tilde_04_low;
        number wrap_tilde_04_high;
        list line_04_target;
        number line_04_time;
        number line_04_grain;
        number line_04_output;
        list message_05_set;
        MillisecondTime _currentTime;
        SampleIndex audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[2];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        int gen_01_counter_0_carry;
        number gen_01_counter_0_count;
        int gen_02_counter_0_carry;
        number gen_02_counter_0_count;
        SampleValue rate_tilde_01_currentPhase;
        SampleValue rate_tilde_01_diff;
        SampleValue rate_tilde_01_prev;
        SampleValue rate_tilde_01_mult;
        SampleValue rate_tilde_01_invmult;
        int rate_tilde_01_wantlock;
        int rate_tilde_01_quant;
        bool rate_tilde_01_setupDone;
        number delta_tilde_01_prev;
        bool delta_tilde_01_setupDone;
        Int numberobj_01_currentFormat;
        number numberobj_01_lastValue;
        number line_01_startTime;
        number line_01_startValue;
        number line_01_currentTarget;
        number line_01_slope;
        number line_01__time;
        list line_01_pendingRamps;
        number param_01_lastValue;
        int gen_03_counter_0_carry;
        number gen_03_counter_0_count;
        SampleValue rate_tilde_02_currentPhase;
        SampleValue rate_tilde_02_diff;
        SampleValue rate_tilde_02_prev;
        SampleValue rate_tilde_02_mult;
        SampleValue rate_tilde_02_invmult;
        int rate_tilde_02_wantlock;
        int rate_tilde_02_quant;
        bool rate_tilde_02_setupDone;
        number delta_tilde_02_prev;
        bool delta_tilde_02_setupDone;
        number line_02_startTime;
        number line_02_startValue;
        number line_02_currentTarget;
        number line_02_slope;
        number line_02__time;
        list line_02_pendingRamps;
        SampleValue rate_tilde_03_currentPhase;
        SampleValue rate_tilde_03_diff;
        SampleValue rate_tilde_03_prev;
        SampleValue rate_tilde_03_mult;
        SampleValue rate_tilde_03_invmult;
        int rate_tilde_03_wantlock;
        int rate_tilde_03_quant;
        bool rate_tilde_03_setupDone;
        number delta_tilde_03_prev;
        bool delta_tilde_03_setupDone;
        int gen_04_counter_0_carry;
        number gen_04_counter_0_count;
        number line_03_startTime;
        number line_03_startValue;
        number line_03_currentTarget;
        number line_03_slope;
        number line_03__time;
        list line_03_pendingRamps;
        int gen_05_counter_0_carry;
        number gen_05_counter_0_count;
        SampleValue rate_tilde_04_currentPhase;
        SampleValue rate_tilde_04_diff;
        SampleValue rate_tilde_04_prev;
        SampleValue rate_tilde_04_mult;
        SampleValue rate_tilde_04_invmult;
        int rate_tilde_04_wantlock;
        int rate_tilde_04_quant;
        bool rate_tilde_04_setupDone;
        number delta_tilde_04_prev;
        bool delta_tilde_04_setupDone;
        number line_04_startTime;
        number line_04_startValue;
        number line_04_currentTarget;
        number line_04_slope;
        number line_04__time;
        list line_04_pendingRamps;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
        RNBOSubpatcher_3774* p_01;
    
};

class RNBOSubpatcher_3776 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_3776()
    {
    }
    
    ~RNBOSubpatcher_3776()
    {
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, -1494586265, false);
    }
    
    number mstosamps(MillisecondTime ms) {
        return ms * this->sr * 0.001;
    }
    
    Index voice() {
        return this->_voiceIndex;
    }
    
    number random(number low, number high) {
        number range = high - low;
        return rand01() * range + low;
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out9 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        this->noise_tilde_02_perform(this->signals[0], n);
        this->dspexpr_08_perform(this->signals[0], this->signals[1], n);
        this->changetilde_02_perform(in1, this->signals[0], n);
        this->dspexpr_09_perform(this->signals[0], this->signals[2], n);
    
        this->sah_tilde_02_perform(
            this->signals[1],
            this->signals[2],
            this->sah_tilde_02_thresh,
            this->signals[0],
            n
        );
    
        this->numbertilde_02_perform(this->signals[0], this->dummyBuffer, n);
        this->dspexpr_10_perform(this->signals[0], this->dspexpr_10_in2, this->signals[1], n);
        this->latch_tilde_02_perform(this->signals[2], this->signals[1], out9, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 3; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        this->numbertilde_02_dspsetup(forceDSPSetup);
        this->latch_tilde_02_dspsetup(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void getPreset(PatcherStateInterface& ) {}
    
    void processTempoEvent(MillisecondTime , Tempo ) {}
    
    void processTransportEvent(MillisecondTime , TransportState ) {}
    
    void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
    
    void onSampleRateChanged(double ) {}
    
    void processTimeSignatureEvent(MillisecondTime , int , int ) {}
    
    void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        default:
            {
            return 0;
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 0;
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(hasValue);
        this->updateTime(time);
    
        switch (index) {
        case -1494586265:
            {
            this->numbertilde_02_value_set(value);
            break;
            }
        }
    }
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("sig"):
            {
            if (TAG("probability_skip[1]/number~_obj-77") == objectId)
                this->numbertilde_02_sig_number_set(payload);
    
            break;
            }
        case TAG("mode"):
            {
            if (TAG("probability_skip[1]/number~_obj-77") == objectId)
                this->numbertilde_02_mode_set(payload);
    
            break;
            }
        }
    }
    
    void processListMessage(
        MessageTag tag,
        MessageTag objectId,
        MillisecondTime time,
        const list& payload
    ) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("sig"):
            {
            if (TAG("probability_skip[1]/number~_obj-77") == objectId)
                this->numbertilde_02_sig_list_set(payload);
    
            break;
            }
        }
    }
    
    void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("monitor"):
            {
            return "monitor";
            }
        case TAG("probability_skip[1]/number~_obj-77"):
            {
            return "probability_skip[1]/number~_obj-77";
            }
        case TAG("assign"):
            {
            return "assign";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("sig"):
            {
            return "sig";
            }
        case TAG("mode"):
            {
            return "mode";
            }
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void numbertilde_02_sig_number_set(number v) {
        this->numbertilde_02_outValue = v;
    }
    
    void numbertilde_02_sig_list_set(const list& v) {
        this->numbertilde_02_outValue = v[0];
    }
    
    void numbertilde_02_mode_set(number v) {
        if (v == 1) {
            this->numbertilde_02_currentMode = 0;
        } else if (v == 2) {
            this->numbertilde_02_currentMode = 1;
        }
    }
    
    void eventinlet_03_out1_bang_bang() {
        this->expr_03_in1_bang();
    }
    
    void eventinlet_03_out1_number_set(number v) {
        this->expr_03_in1_set(v);
    }
    
    void eventinlet_03_out1_list_set(const list& v) {
        {
            if (v->length > 1)
                this->expr_03_in2_set(v[1]);
    
            number converted = (v->length > 0 ? v[0] : 0);
            this->expr_03_in1_set(converted);
        }
    }
    
    void numbertilde_02_value_set(number ) {}
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 1;
    }
    
    Index getNumOutputChannels() const {
        return 1;
    }
    
    void initializeObjects() {
        this->numbertilde_02_init();
        this->noise_tilde_02_init();
        this->changetilde_02_ch_init();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void allocateDataRefs() {}
    
    void dspexpr_10_in2_set(number v) {
        this->dspexpr_10_in2 = v;
    }
    
    void sah_tilde_02_thresh_set(number v) {
        this->sah_tilde_02_thresh = v;
    }
    
    void expr_04_out1_set(number v) {
        this->expr_04_out1 = v;
        this->dspexpr_10_in2_set(this->expr_04_out1);
        this->sah_tilde_02_thresh_set(this->expr_04_out1);
    }
    
    void expr_04_in1_set(number in1) {
        this->expr_04_in1 = in1;
        this->expr_04_out1_set(this->expr_04_in1 - this->expr_04_in2);//#map:probability_skip[1]/-_obj-5:1
    }
    
    void expr_03_out1_set(number v) {
        this->expr_03_out1 = v;
        this->expr_04_in1_set(this->expr_03_out1);
    }
    
    void expr_03_in1_bang() {
        this->expr_03_out1_set(this->expr_03_in1 + this->expr_03_in2);//#map:probability_skip[1]/+_obj-6:1
    }
    
    void expr_03_in1_set(number in1) {
        this->expr_03_in1 = in1;
        this->expr_03_out1_set(this->expr_03_in1 + this->expr_03_in2);//#map:probability_skip[1]/+_obj-6:1
    }
    
    void expr_03_in2_set(number v) {
        this->expr_03_in2 = v;
    }
    
    void noise_tilde_02_perform(SampleValue * out1, Index n) {
        auto __noise_tilde_02_state = this->noise_tilde_02_state;
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = xoshiro_next(__noise_tilde_02_state);
        }
    }
    
    void dspexpr_08_perform(const Sample * in1, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = rnbo_abs(in1[(Index)i]);//#map:_###_obj_###_:1
        }
    }
    
    void changetilde_02_perform(const Sample * input, SampleValue * out, Index n) {
        for (Index i = 0; i < n; i++) {
            out[(Index)i] = this->changetilde_02_ch_next(input[(Index)i]);
        }
    }
    
    void dspexpr_09_perform(const Sample * in1, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = rnbo_abs(in1[(Index)i]);//#map:_###_obj_###_:1
        }
    }
    
    void sah_tilde_02_perform(
        const Sample * input,
        const Sample * trig,
        number thresh,
        SampleValue * out,
        Index n
    ) {
        for (Index i = 0; i < n; i++) {
            out[(Index)i] = this->sah_tilde_02_s_next(input[(Index)i], trig[(Index)i], thresh);
        }
    }
    
    void numbertilde_02_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
        auto __numbertilde_02_currentIntervalInSamples = this->numbertilde_02_currentIntervalInSamples;
        auto __numbertilde_02_lastValue = this->numbertilde_02_lastValue;
        auto __numbertilde_02_currentInterval = this->numbertilde_02_currentInterval;
        auto __numbertilde_02_rampInSamples = this->numbertilde_02_rampInSamples;
        auto __numbertilde_02_outValue = this->numbertilde_02_outValue;
        auto __numbertilde_02_currentMode = this->numbertilde_02_currentMode;
        number monitorvalue = input_signal[0];
    
        for (Index i = 0; i < n; i++) {
            if (__numbertilde_02_currentMode == 0) {
                output[(Index)i] = this->numbertilde_02_smooth_next(
                    __numbertilde_02_outValue,
                    __numbertilde_02_rampInSamples,
                    __numbertilde_02_rampInSamples
                );
            } else {
                output[(Index)i] = input_signal[(Index)i];
            }
        }
    
        __numbertilde_02_currentInterval -= n;
    
        if (monitorvalue != __numbertilde_02_lastValue && __numbertilde_02_currentInterval <= 0) {
            __numbertilde_02_currentInterval = __numbertilde_02_currentIntervalInSamples;
    
            this->getEngine()->scheduleClockEventWithValue(
                this,
                -1494586265,
                this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                monitorvalue
            );;
    
            __numbertilde_02_lastValue = monitorvalue;
    
            this->getEngine()->sendListMessage(
                TAG("monitor"),
                TAG("probability_skip[1]/number~_obj-77"),
                {monitorvalue},
                this->_currentTime
            );;
        }
    
        this->numbertilde_02_currentInterval = __numbertilde_02_currentInterval;
        this->numbertilde_02_lastValue = __numbertilde_02_lastValue;
    }
    
    void dspexpr_10_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] >= in2;//#map:_###_obj_###_:1
        }
    }
    
    void latch_tilde_02_perform(const Sample * x, const Sample * control, SampleValue * out1, Index n) {
        auto __latch_tilde_02_value = this->latch_tilde_02_value;
        Index i;
    
        for (i = 0; i < n; i++) {
            if (control[(Index)i] != 0.)
                __latch_tilde_02_value = x[(Index)i];
    
            out1[(Index)i] = __latch_tilde_02_value;
        }
    
        this->latch_tilde_02_value = __latch_tilde_02_value;
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void latch_tilde_02_reset() {
        this->latch_tilde_02_value = 0;
    }
    
    void latch_tilde_02_dspsetup(bool force) {
        if ((bool)(this->latch_tilde_02_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->latch_tilde_02_reset();
        this->latch_tilde_02_setupDone = true;
    }
    
    number numbertilde_02_smooth_d_next(number x) {
        number temp = (number)(x - this->numbertilde_02_smooth_d_prev);
        this->numbertilde_02_smooth_d_prev = x;
        return temp;
    }
    
    void numbertilde_02_smooth_d_dspsetup() {
        this->numbertilde_02_smooth_d_reset();
    }
    
    void numbertilde_02_smooth_d_reset() {
        this->numbertilde_02_smooth_d_prev = 0;
    }
    
    number numbertilde_02_smooth_next(number x, number up, number down) {
        if (this->numbertilde_02_smooth_d_next(x) != 0.) {
            if (x > this->numbertilde_02_smooth_prev) {
                number _up = up;
    
                if (_up < 1)
                    _up = 1;
    
                this->numbertilde_02_smooth_index = _up;
                this->numbertilde_02_smooth_increment = (x - this->numbertilde_02_smooth_prev) / _up;
            } else if (x < this->numbertilde_02_smooth_prev) {
                number _down = down;
    
                if (_down < 1)
                    _down = 1;
    
                this->numbertilde_02_smooth_index = _down;
                this->numbertilde_02_smooth_increment = (x - this->numbertilde_02_smooth_prev) / _down;
            }
        }
    
        if (this->numbertilde_02_smooth_index > 0) {
            this->numbertilde_02_smooth_prev += this->numbertilde_02_smooth_increment;
            this->numbertilde_02_smooth_index -= 1;
        } else {
            this->numbertilde_02_smooth_prev = x;
        }
    
        return this->numbertilde_02_smooth_prev;
    }
    
    void numbertilde_02_smooth_reset() {
        this->numbertilde_02_smooth_prev = 0;
        this->numbertilde_02_smooth_index = 0;
        this->numbertilde_02_smooth_increment = 0;
        this->numbertilde_02_smooth_d_reset();
    }
    
    void numbertilde_02_init() {
        this->numbertilde_02_currentMode = 1;
    
        this->getEngine()->sendNumMessage(
            TAG("setup"),
            TAG("probability_skip[1]/number~_obj-77"),
            1,
            this->_currentTime
        );
    }
    
    void numbertilde_02_dspsetup(bool force) {
        if ((bool)(this->numbertilde_02_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->numbertilde_02_currentIntervalInSamples = this->mstosamps(100);
        this->numbertilde_02_currentInterval = this->numbertilde_02_currentIntervalInSamples;
        this->numbertilde_02_rampInSamples = this->mstosamps(this->numbertilde_02_ramp);
        this->numbertilde_02_setupDone = true;
        this->numbertilde_02_smooth_d_dspsetup();
    }
    
    number sah_tilde_02_s_next(number x, number trig, number thresh) {
        if (this->sah_tilde_02_s_prev <= thresh && trig > thresh)
            this->sah_tilde_02_s_value = x;
    
        this->sah_tilde_02_s_prev = trig;
        return this->sah_tilde_02_s_value;
    }
    
    void sah_tilde_02_s_reset() {
        this->sah_tilde_02_s_prev = 0.;
        this->sah_tilde_02_s_value = 0.;
    }
    
    void noise_tilde_02_init() {
        this->noise_tilde_02_reset();
    }
    
    void noise_tilde_02_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->noise_tilde_02_state
        );
    }
    
    number changetilde_02_ch_next(number x) {
        number temp = x - this->changetilde_02_ch_prev;
        this->changetilde_02_ch_prev = x;
        return (temp > 0. ? 1. : (temp < 0. ? -1. : 0));
    }
    
    void changetilde_02_ch_init() {
        this->changetilde_02_ch_prev = 0;
    }
    
    void changetilde_02_ch_reset() {
        this->changetilde_02_ch_prev = 0;
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        latch_tilde_02_x = 0;
        latch_tilde_02_control = 0;
        numbertilde_02_input_number = 0;
        numbertilde_02_ramp = 0;
        dspexpr_08_in1 = 0;
        sah_tilde_02_input = 0;
        sah_tilde_02_trig = -1;
        sah_tilde_02_thresh = 0.5;
        changetilde_02_input = 0;
        dspexpr_09_in1 = 0;
        dspexpr_10_in1 = 0;
        dspexpr_10_in2 = 0;
        expr_03_in1 = 0;
        expr_03_in2 = 1;
        expr_03_out1 = 0;
        expr_04_in1 = 0;
        expr_04_in2 = 1;
        expr_04_out1 = 0;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        signals[2] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        latch_tilde_02_value = 0;
        latch_tilde_02_setupDone = false;
        numbertilde_02_currentInterval = 0;
        numbertilde_02_currentIntervalInSamples = 0;
        numbertilde_02_lastValue = 0;
        numbertilde_02_outValue = 0;
        numbertilde_02_rampInSamples = 0;
        numbertilde_02_currentMode = 0;
        numbertilde_02_smooth_d_prev = 0;
        numbertilde_02_smooth_prev = 0;
        numbertilde_02_smooth_index = 0;
        numbertilde_02_smooth_increment = 0;
        numbertilde_02_setupDone = false;
        sah_tilde_02_s_prev = 0;
        sah_tilde_02_s_value = 0;
        changetilde_02_ch_prev = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number latch_tilde_02_x;
        number latch_tilde_02_control;
        number numbertilde_02_input_number;
        number numbertilde_02_ramp;
        number dspexpr_08_in1;
        number sah_tilde_02_input;
        number sah_tilde_02_trig;
        number sah_tilde_02_thresh;
        number changetilde_02_input;
        number dspexpr_09_in1;
        number dspexpr_10_in1;
        number dspexpr_10_in2;
        number expr_03_in1;
        number expr_03_in2;
        number expr_03_out1;
        number expr_04_in1;
        number expr_04_in2;
        number expr_04_out1;
        MillisecondTime _currentTime;
        SampleIndex audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[3];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        number latch_tilde_02_value;
        bool latch_tilde_02_setupDone;
        SampleIndex numbertilde_02_currentInterval;
        SampleIndex numbertilde_02_currentIntervalInSamples;
        number numbertilde_02_lastValue;
        number numbertilde_02_outValue;
        number numbertilde_02_rampInSamples;
        Int numbertilde_02_currentMode;
        number numbertilde_02_smooth_d_prev;
        number numbertilde_02_smooth_prev;
        number numbertilde_02_smooth_index;
        number numbertilde_02_smooth_increment;
        bool numbertilde_02_setupDone;
        number sah_tilde_02_s_prev;
        number sah_tilde_02_s_value;
        UInt noise_tilde_02_state[4] = { };
        number changetilde_02_ch_prev;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_3777 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_3777()
    {
    }
    
    ~RNBOSubpatcher_3777()
    {
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, -871642103, false);
        getEngine()->flushClockEvents(this, 1964277200, false);
        getEngine()->flushClockEvents(this, 1592269969, false);
        getEngine()->flushClockEvents(this, 1220262738, false);
        getEngine()->flushClockEvents(this, 848255507, false);
    }
    
    inline number safemod(number f, number m) {
        if (m != 0) {
            Int f_trunc = (Int)(trunc(f));
            Int m_trunc = (Int)(trunc(m));
    
            if (f == f_trunc && m == m_trunc) {
                f = f_trunc % m_trunc;
            } else {
                if (m < 0) {
                    m = -m;
                }
    
                if (f >= m) {
                    if (f >= m * 2.0) {
                        number d = f / m;
                        Int i = (Int)(trunc(d));
                        d = d - i;
                        f = d * m;
                    } else {
                        f -= m;
                    }
                } else if (f <= -m) {
                    if (f <= -m * 2.0) {
                        number d = f / m;
                        Int i = (Int)(trunc(d));
                        d = d - i;
                        f = d * m;
                    } else {
                        f += m;
                    }
                }
            }
        } else {
            f = 0.0;
        }
    
        return f;
    }
    
    inline number safediv(number num, number denom) {
        return (denom == 0.0 ? 0.0 : num / denom);
    }
    
    number quantize(number value, number quantum) {
        return rnbo_floor(value * quantum + 0.5) / quantum;
    }
    
    MillisecondTime currenttime() {
        return this->_currentTime;
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out7 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out8 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        SampleValue * out9 = (numOutputs >= 3 && outputs[2] ? outputs[2] : this->dummyBuffer);
        SampleValue * out10 = (numOutputs >= 4 && outputs[3] ? outputs[3] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        this->rate_tilde_05_perform(in1, this->rate_tilde_05_multiplier, this->signals[0], n);
    
        this->wrap_tilde_05_perform(
            this->signals[0],
            this->wrap_tilde_05_low,
            this->wrap_tilde_05_high,
            this->signals[1],
            n
        );
    
        this->delta_tilde_05_perform(this->signals[1], this->signals[0], n);
        this->dspexpr_11_perform(this->signals[0], this->dspexpr_11_in2, this->signals[1], n);
        this->gen_06_perform(this->signals[1], out7, n);
        this->rate_tilde_06_perform(in1, this->rate_tilde_06_multiplier, this->signals[1], n);
    
        this->wrap_tilde_06_perform(
            this->signals[1],
            this->wrap_tilde_06_low,
            this->wrap_tilde_06_high,
            this->signals[0],
            n
        );
    
        this->delta_tilde_06_perform(this->signals[0], this->signals[1], n);
        this->dspexpr_12_perform(this->signals[1], this->dspexpr_12_in2, this->signals[0], n);
        this->gen_07_perform(this->signals[0], out8, n);
        this->rate_tilde_07_perform(in1, this->rate_tilde_07_multiplier, this->signals[0], n);
    
        this->wrap_tilde_07_perform(
            this->signals[0],
            this->wrap_tilde_07_low,
            this->wrap_tilde_07_high,
            this->signals[1],
            n
        );
    
        this->delta_tilde_07_perform(this->signals[1], this->signals[0], n);
        this->dspexpr_13_perform(this->signals[0], this->dspexpr_13_in2, this->signals[1], n);
        this->gen_08_perform(this->signals[1], out9, n);
        this->rate_tilde_08_perform(in1, this->rate_tilde_08_multiplier, this->signals[1], n);
    
        this->wrap_tilde_08_perform(
            this->signals[1],
            this->wrap_tilde_08_low,
            this->wrap_tilde_08_high,
            this->signals[0],
            n
        );
    
        this->delta_tilde_08_perform(this->signals[0], this->signals[1], n);
        this->dspexpr_14_perform(this->signals[1], this->dspexpr_14_in2, this->signals[0], n);
        this->gen_09_perform(this->signals[0], out10, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 2; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        this->rate_tilde_05_dspsetup(forceDSPSetup);
        this->delta_tilde_05_dspsetup(forceDSPSetup);
        this->rate_tilde_06_dspsetup(forceDSPSetup);
        this->delta_tilde_06_dspsetup(forceDSPSetup);
        this->rate_tilde_07_dspsetup(forceDSPSetup);
        this->delta_tilde_07_dspsetup(forceDSPSetup);
        this->rate_tilde_08_dspsetup(forceDSPSetup);
        this->delta_tilde_08_dspsetup(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void getPreset(PatcherStateInterface& ) {}
    
    void processTempoEvent(MillisecondTime , Tempo ) {}
    
    void processTransportEvent(MillisecondTime , TransportState ) {}
    
    void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
    
    void onSampleRateChanged(double ) {}
    
    void processTimeSignatureEvent(MillisecondTime , int , int ) {}
    
    void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        default:
            {
            return 0;
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 0;
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(hasValue);
        this->updateTime(time);
    
        switch (index) {
        case -871642103:
            {
            this->loadbang_02_startupbang_bang();
            break;
            }
        case 1964277200:
            {
            this->line_05_tick_set(value);
            break;
            }
        case 1592269969:
            {
            this->line_06_tick_set(value);
            break;
            }
        case 1220262738:
            {
            this->line_07_tick_set(value);
            break;
            }
        case 848255507:
            {
            this->line_08_tick_set(value);
            break;
            }
        }
    }
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("valin"):
            {
            if (TAG("rotating_clock_divider/number_obj-66") == objectId)
                this->numberobj_02_valin_set(payload);
    
            break;
            }
        case TAG("format"):
            {
            if (TAG("rotating_clock_divider/number_obj-66") == objectId)
                this->numberobj_02_format_set(payload);
    
            break;
            }
        case TAG("listin"):
            {
            if (TAG("rotating_clock_divider/message_obj-53") == objectId)
                this->message_06_listin_number_set(payload);
    
            if (TAG("rotating_clock_divider/message_obj-130") == objectId)
                this->message_07_listin_number_set(payload);
    
            if (TAG("rotating_clock_divider/message_obj-131") == objectId)
                this->message_08_listin_number_set(payload);
    
            if (TAG("rotating_clock_divider/message_obj-132") == objectId)
                this->message_09_listin_number_set(payload);
    
            if (TAG("rotating_clock_divider/message_obj-133") == objectId)
                this->message_10_listin_number_set(payload);
    
            break;
            }
        }
    }
    
    void processListMessage(
        MessageTag tag,
        MessageTag objectId,
        MillisecondTime time,
        const list& payload
    ) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("listin"):
            {
            if (TAG("rotating_clock_divider/message_obj-53") == objectId)
                this->message_06_listin_list_set(payload);
    
            if (TAG("rotating_clock_divider/message_obj-130") == objectId)
                this->message_07_listin_list_set(payload);
    
            if (TAG("rotating_clock_divider/message_obj-131") == objectId)
                this->message_08_listin_list_set(payload);
    
            if (TAG("rotating_clock_divider/message_obj-132") == objectId)
                this->message_09_listin_list_set(payload);
    
            if (TAG("rotating_clock_divider/message_obj-133") == objectId)
                this->message_10_listin_list_set(payload);
    
            break;
            }
        }
    }
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("bangin"):
            {
            if (TAG("rotating_clock_divider/button_obj-57") == objectId)
                this->button_02_bangin_bang();
    
            break;
            }
        case TAG("startupbang"):
            {
            if (TAG("rotating_clock_divider/loadbang_obj-168") == objectId)
                this->loadbang_02_startupbang_bang();
    
            break;
            }
        case TAG("listin"):
            {
            if (TAG("rotating_clock_divider/message_obj-53") == objectId)
                this->message_06_listin_bang_bang();
    
            if (TAG("rotating_clock_divider/message_obj-130") == objectId)
                this->message_07_listin_bang_bang();
    
            if (TAG("rotating_clock_divider/message_obj-131") == objectId)
                this->message_08_listin_bang_bang();
    
            if (TAG("rotating_clock_divider/message_obj-132") == objectId)
                this->message_09_listin_bang_bang();
    
            if (TAG("rotating_clock_divider/message_obj-133") == objectId)
                this->message_10_listin_bang_bang();
    
            break;
            }
        }
    }
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("valout"):
            {
            return "valout";
            }
        case TAG("rotating_clock_divider/number_obj-66"):
            {
            return "rotating_clock_divider/number_obj-66";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("bangout"):
            {
            return "bangout";
            }
        case TAG("rotating_clock_divider/button_obj-57"):
            {
            return "rotating_clock_divider/button_obj-57";
            }
        case TAG("listout"):
            {
            return "listout";
            }
        case TAG("rotating_clock_divider/message_obj-53"):
            {
            return "rotating_clock_divider/message_obj-53";
            }
        case TAG("rotating_clock_divider/message_obj-130"):
            {
            return "rotating_clock_divider/message_obj-130";
            }
        case TAG("rotating_clock_divider/message_obj-131"):
            {
            return "rotating_clock_divider/message_obj-131";
            }
        case TAG("rotating_clock_divider/message_obj-132"):
            {
            return "rotating_clock_divider/message_obj-132";
            }
        case TAG("rotating_clock_divider/message_obj-133"):
            {
            return "rotating_clock_divider/message_obj-133";
            }
        case TAG("valin"):
            {
            return "valin";
            }
        case TAG("format"):
            {
            return "format";
            }
        case TAG("bangin"):
            {
            return "bangin";
            }
        case TAG("startupbang"):
            {
            return "startupbang";
            }
        case TAG("rotating_clock_divider/loadbang_obj-168"):
            {
            return "rotating_clock_divider/loadbang_obj-168";
            }
        case TAG("listin"):
            {
            return "listin";
            }
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void numberobj_02_valin_set(number v) {
        this->numberobj_02_value_set(v);
    }
    
    void numberobj_02_format_set(number v) {
        this->numberobj_02_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void button_02_bangin_bang() {
        this->button_02_bangval_bang();
    }
    
    void eventinlet_04_out1_bang_bang() {
        this->numberobj_02_value_bang();
    }
    
    void eventinlet_04_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_02_value_set(converted);
        }
    }
    
    void loadbang_02_startupbang_bang() {
        this->loadbang_02_output_bang();
    }
    
    void message_06_listin_list_set(const list& v) {
        this->message_06_set_set(v);
    }
    
    void message_06_listin_number_set(number v) {
        this->message_06_set_set(v);
    }
    
    void message_06_listin_bang_bang() {
        this->message_06_trigger_bang();
    }
    
    void line_05_tick_set(number v) {
        this->line_05_output_set(v);
    
        if ((bool)(this->line_05_isFinished(v))) {
            this->line_05_slope = 0;
            this->line_05_startValue = v;
            this->line_05_startPendingRamp();
        } else {
            this->line_05_scheduleNext();
        }
    }
    
    void message_07_listin_list_set(const list& v) {
        this->message_07_set_set(v);
    }
    
    void message_07_listin_number_set(number v) {
        this->message_07_set_set(v);
    }
    
    void message_07_listin_bang_bang() {
        this->message_07_trigger_bang();
    }
    
    void line_06_tick_set(number v) {
        this->line_06_output_set(v);
    
        if ((bool)(this->line_06_isFinished(v))) {
            this->line_06_slope = 0;
            this->line_06_startValue = v;
            this->line_06_startPendingRamp();
        } else {
            this->line_06_scheduleNext();
        }
    }
    
    void message_08_listin_list_set(const list& v) {
        this->message_08_set_set(v);
    }
    
    void message_08_listin_number_set(number v) {
        this->message_08_set_set(v);
    }
    
    void message_08_listin_bang_bang() {
        this->message_08_trigger_bang();
    }
    
    void line_07_tick_set(number v) {
        this->line_07_output_set(v);
    
        if ((bool)(this->line_07_isFinished(v))) {
            this->line_07_slope = 0;
            this->line_07_startValue = v;
            this->line_07_startPendingRamp();
        } else {
            this->line_07_scheduleNext();
        }
    }
    
    void message_09_listin_list_set(const list& v) {
        this->message_09_set_set(v);
    }
    
    void message_09_listin_number_set(number v) {
        this->message_09_set_set(v);
    }
    
    void message_09_listin_bang_bang() {
        this->message_09_trigger_bang();
    }
    
    void line_08_tick_set(number v) {
        this->line_08_output_set(v);
    
        if ((bool)(this->line_08_isFinished(v))) {
            this->line_08_slope = 0;
            this->line_08_startValue = v;
            this->line_08_startPendingRamp();
        } else {
            this->line_08_scheduleNext();
        }
    }
    
    void message_10_listin_list_set(const list& v) {
        this->message_10_set_set(v);
    }
    
    void message_10_listin_number_set(number v) {
        this->message_10_set_set(v);
    }
    
    void message_10_listin_bang_bang() {
        this->message_10_trigger_bang();
    }
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 1;
    }
    
    Index getNumOutputChannels() const {
        return 4;
    }
    
    void initializeObjects() {
        this->numberobj_02_init();
        this->gen_06_counter_0_init();
        this->message_06_init();
        this->message_07_init();
        this->gen_07_counter_0_init();
        this->message_08_init();
        this->gen_08_counter_0_init();
        this->message_09_init();
        this->gen_09_counter_0_init();
        this->message_10_init();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime());
        this->getEngine()->scheduleClockEvent(this, -871642103, 0 + this->_currentTime);;
    }
    
    void allocateDataRefs() {}
    
    void listrot_02_shift_set(number v) {
        this->listrot_02_shift = v;
    }
    
    void message_10_set_set(const list& v) {
        this->message_10_set = jsCreateListCopy(v);
    
        this->getEngine()->sendListMessage(
            TAG("listout"),
            TAG("rotating_clock_divider/message_obj-133"),
            v,
            this->_currentTime
        );
    }
    
    static number line_08_time_constrain(number v) {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void line_08_time_set(number v) {
        v = this->line_08_time_constrain(v);
        this->line_08_time = v;
    }
    
    void rate_tilde_08_multiplier_set(number v) {
        this->rate_tilde_08_multiplier = v;
    }
    
    void line_08_output_set(number v) {
        this->line_08_output = v;
        this->rate_tilde_08_multiplier_set(v);
    }
    
    void line_08_stop_bang() {
        this->getEngine()->flushClockEvents(this, 848255507, false);;
        this->line_08_pendingRamps->length = 0;
        this->line_08_startValue = this->line_08_output;
        this->line_08_slope = 0;
        this->line_08__time = 0;
        this->line_08_time_set(0);
    }
    
    static number line_08_grain_constrain(number v) {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void line_08_grain_set(number v) {
        v = this->line_08_grain_constrain(v);
        this->line_08_grain = v;
    
        if ((bool)(!(bool)(this->line_08_isFinished(this->line_08_startValue)))) {
            this->getEngine()->flushClockEvents(this, 848255507, false);;
            this->line_08_scheduleNext();
        }
    }
    
    void line_08_end_bang() {}
    
    void line_08_target_set(const list& v) {
        this->line_08_target = jsCreateListCopy(v);
        this->line_08_pendingRamps->length = 0;
    
        if (v->length == 1) {
            this->line_08__time = this->line_08_time;
            this->line_08_time_set(0);
    
            if ((bool)(this->line_08__time))
                this->line_08_startRamp(v[0], this->line_08__time);
            else {
                this->line_08_output_set(v[0]);
                this->line_08_startValue = v[0];
                this->line_08_stop_bang();
            }
        } else if (v->length == 2) {
            this->line_08_time_set(0);
            this->line_08__time = (v[1] < 0 ? 0 : v[1]);
            this->line_08_startRamp(v[0], this->line_08__time);
        } else if (v->length == 3) {
            this->line_08_time_set(0);
            this->line_08_grain_set(v[2]);
            this->line_08__time = (v[1] < 0 ? 0 : v[1]);
            this->line_08_startRamp(v[0], this->line_08__time);
        } else {
            this->line_08_time_set(0);
            this->line_08_pendingRamps = jsCreateListCopy(v);
            this->line_08_startPendingRamp();
        }
    }
    
    void message_10_out_set(const list& v) {
        this->line_08_target_set(v);
    }
    
    void message_10_trigger_bang() {
        this->message_10_out_set(this->message_10_set);
    }
    
    void unpack_02_out8_set(number v) {
        this->unpack_02_out8 = v;
    
        {
            list converted = {v};
            this->message_10_set_set(converted);
        }
    
        this->message_10_trigger_bang();
    }
    
    void message_09_set_set(const list& v) {
        this->message_09_set = jsCreateListCopy(v);
    
        this->getEngine()->sendListMessage(
            TAG("listout"),
            TAG("rotating_clock_divider/message_obj-132"),
            v,
            this->_currentTime
        );
    }
    
    static number line_07_time_constrain(number v) {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void line_07_time_set(number v) {
        v = this->line_07_time_constrain(v);
        this->line_07_time = v;
    }
    
    void rate_tilde_07_multiplier_set(number v) {
        this->rate_tilde_07_multiplier = v;
    }
    
    void line_07_output_set(number v) {
        this->line_07_output = v;
        this->rate_tilde_07_multiplier_set(v);
    }
    
    void line_07_stop_bang() {
        this->getEngine()->flushClockEvents(this, 1220262738, false);;
        this->line_07_pendingRamps->length = 0;
        this->line_07_startValue = this->line_07_output;
        this->line_07_slope = 0;
        this->line_07__time = 0;
        this->line_07_time_set(0);
    }
    
    static number line_07_grain_constrain(number v) {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void line_07_grain_set(number v) {
        v = this->line_07_grain_constrain(v);
        this->line_07_grain = v;
    
        if ((bool)(!(bool)(this->line_07_isFinished(this->line_07_startValue)))) {
            this->getEngine()->flushClockEvents(this, 1220262738, false);;
            this->line_07_scheduleNext();
        }
    }
    
    void line_07_end_bang() {}
    
    void line_07_target_set(const list& v) {
        this->line_07_target = jsCreateListCopy(v);
        this->line_07_pendingRamps->length = 0;
    
        if (v->length == 1) {
            this->line_07__time = this->line_07_time;
            this->line_07_time_set(0);
    
            if ((bool)(this->line_07__time))
                this->line_07_startRamp(v[0], this->line_07__time);
            else {
                this->line_07_output_set(v[0]);
                this->line_07_startValue = v[0];
                this->line_07_stop_bang();
            }
        } else if (v->length == 2) {
            this->line_07_time_set(0);
            this->line_07__time = (v[1] < 0 ? 0 : v[1]);
            this->line_07_startRamp(v[0], this->line_07__time);
        } else if (v->length == 3) {
            this->line_07_time_set(0);
            this->line_07_grain_set(v[2]);
            this->line_07__time = (v[1] < 0 ? 0 : v[1]);
            this->line_07_startRamp(v[0], this->line_07__time);
        } else {
            this->line_07_time_set(0);
            this->line_07_pendingRamps = jsCreateListCopy(v);
            this->line_07_startPendingRamp();
        }
    }
    
    void message_09_out_set(const list& v) {
        this->line_07_target_set(v);
    }
    
    void message_09_trigger_bang() {
        this->message_09_out_set(this->message_09_set);
    }
    
    void unpack_02_out7_set(number v) {
        this->unpack_02_out7 = v;
    
        {
            list converted = {v};
            this->message_09_set_set(converted);
        }
    
        this->message_09_trigger_bang();
    }
    
    void message_08_set_set(const list& v) {
        this->message_08_set = jsCreateListCopy(v);
    
        this->getEngine()->sendListMessage(
            TAG("listout"),
            TAG("rotating_clock_divider/message_obj-131"),
            v,
            this->_currentTime
        );
    }
    
    static number line_06_time_constrain(number v) {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void line_06_time_set(number v) {
        v = this->line_06_time_constrain(v);
        this->line_06_time = v;
    }
    
    void rate_tilde_06_multiplier_set(number v) {
        this->rate_tilde_06_multiplier = v;
    }
    
    void line_06_output_set(number v) {
        this->line_06_output = v;
        this->rate_tilde_06_multiplier_set(v);
    }
    
    void line_06_stop_bang() {
        this->getEngine()->flushClockEvents(this, 1592269969, false);;
        this->line_06_pendingRamps->length = 0;
        this->line_06_startValue = this->line_06_output;
        this->line_06_slope = 0;
        this->line_06__time = 0;
        this->line_06_time_set(0);
    }
    
    static number line_06_grain_constrain(number v) {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void line_06_grain_set(number v) {
        v = this->line_06_grain_constrain(v);
        this->line_06_grain = v;
    
        if ((bool)(!(bool)(this->line_06_isFinished(this->line_06_startValue)))) {
            this->getEngine()->flushClockEvents(this, 1592269969, false);;
            this->line_06_scheduleNext();
        }
    }
    
    void line_06_end_bang() {}
    
    void line_06_target_set(const list& v) {
        this->line_06_target = jsCreateListCopy(v);
        this->line_06_pendingRamps->length = 0;
    
        if (v->length == 1) {
            this->line_06__time = this->line_06_time;
            this->line_06_time_set(0);
    
            if ((bool)(this->line_06__time))
                this->line_06_startRamp(v[0], this->line_06__time);
            else {
                this->line_06_output_set(v[0]);
                this->line_06_startValue = v[0];
                this->line_06_stop_bang();
            }
        } else if (v->length == 2) {
            this->line_06_time_set(0);
            this->line_06__time = (v[1] < 0 ? 0 : v[1]);
            this->line_06_startRamp(v[0], this->line_06__time);
        } else if (v->length == 3) {
            this->line_06_time_set(0);
            this->line_06_grain_set(v[2]);
            this->line_06__time = (v[1] < 0 ? 0 : v[1]);
            this->line_06_startRamp(v[0], this->line_06__time);
        } else {
            this->line_06_time_set(0);
            this->line_06_pendingRamps = jsCreateListCopy(v);
            this->line_06_startPendingRamp();
        }
    }
    
    void message_08_out_set(const list& v) {
        this->line_06_target_set(v);
    }
    
    void message_08_trigger_bang() {
        this->message_08_out_set(this->message_08_set);
    }
    
    void unpack_02_out6_set(number v) {
        this->unpack_02_out6 = v;
    
        {
            list converted = {v};
            this->message_08_set_set(converted);
        }
    
        this->message_08_trigger_bang();
    }
    
    void message_07_set_set(const list& v) {
        this->message_07_set = jsCreateListCopy(v);
    
        this->getEngine()->sendListMessage(
            TAG("listout"),
            TAG("rotating_clock_divider/message_obj-130"),
            v,
            this->_currentTime
        );
    }
    
    static number line_05_time_constrain(number v) {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void line_05_time_set(number v) {
        v = this->line_05_time_constrain(v);
        this->line_05_time = v;
    }
    
    void rate_tilde_05_multiplier_set(number v) {
        this->rate_tilde_05_multiplier = v;
    }
    
    void line_05_output_set(number v) {
        this->line_05_output = v;
        this->rate_tilde_05_multiplier_set(v);
    }
    
    void line_05_stop_bang() {
        this->getEngine()->flushClockEvents(this, 1964277200, false);;
        this->line_05_pendingRamps->length = 0;
        this->line_05_startValue = this->line_05_output;
        this->line_05_slope = 0;
        this->line_05__time = 0;
        this->line_05_time_set(0);
    }
    
    static number line_05_grain_constrain(number v) {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void line_05_grain_set(number v) {
        v = this->line_05_grain_constrain(v);
        this->line_05_grain = v;
    
        if ((bool)(!(bool)(this->line_05_isFinished(this->line_05_startValue)))) {
            this->getEngine()->flushClockEvents(this, 1964277200, false);;
            this->line_05_scheduleNext();
        }
    }
    
    void line_05_end_bang() {}
    
    void line_05_target_set(const list& v) {
        this->line_05_target = jsCreateListCopy(v);
        this->line_05_pendingRamps->length = 0;
    
        if (v->length == 1) {
            this->line_05__time = this->line_05_time;
            this->line_05_time_set(0);
    
            if ((bool)(this->line_05__time))
                this->line_05_startRamp(v[0], this->line_05__time);
            else {
                this->line_05_output_set(v[0]);
                this->line_05_startValue = v[0];
                this->line_05_stop_bang();
            }
        } else if (v->length == 2) {
            this->line_05_time_set(0);
            this->line_05__time = (v[1] < 0 ? 0 : v[1]);
            this->line_05_startRamp(v[0], this->line_05__time);
        } else if (v->length == 3) {
            this->line_05_time_set(0);
            this->line_05_grain_set(v[2]);
            this->line_05__time = (v[1] < 0 ? 0 : v[1]);
            this->line_05_startRamp(v[0], this->line_05__time);
        } else {
            this->line_05_time_set(0);
            this->line_05_pendingRamps = jsCreateListCopy(v);
            this->line_05_startPendingRamp();
        }
    }
    
    void message_07_out_set(const list& v) {
        this->line_05_target_set(v);
    }
    
    void message_07_trigger_bang() {
        this->message_07_out_set(this->message_07_set);
    }
    
    void unpack_02_out5_set(number v) {
        this->unpack_02_out5 = v;
    
        {
            list converted = {v};
            this->message_07_set_set(converted);
        }
    
        this->message_07_trigger_bang();
    }
    
    void unpack_02_out4_set(number v) {
        this->unpack_02_out4 = v;
    }
    
    void unpack_02_out3_set(number v) {
        this->unpack_02_out3 = v;
    }
    
    void unpack_02_out2_set(number v) {
        this->unpack_02_out2 = v;
    }
    
    void unpack_02_out1_set(number v) {
        this->unpack_02_out1 = v;
    }
    
    void unpack_02_input_list_set(const list& v) {
        if (v->length > 7)
            this->unpack_02_out8_set(v[7]);
    
        if (v->length > 6)
            this->unpack_02_out7_set(v[6]);
    
        if (v->length > 5)
            this->unpack_02_out6_set(v[5]);
    
        if (v->length > 4)
            this->unpack_02_out5_set(v[4]);
    
        if (v->length > 3)
            this->unpack_02_out4_set(v[3]);
    
        if (v->length > 2)
            this->unpack_02_out3_set(v[2]);
    
        if (v->length > 1)
            this->unpack_02_out2_set(v[1]);
    
        if (v->length > 0)
            this->unpack_02_out1_set(v[0]);
    }
    
    void listrot_02_out1_set(const list& v) {
        this->unpack_02_input_list_set(v);
    }
    
    void listrot_02_input_bang() {
        list input = this->listrot_02_input;
        auto shift = this->listrot_02_shift;
        list tmp = jsCreateListCopy(input);
    
        if (tmp->length > 0) {
            if (shift > 0) {
                for (Index i = 0; i < shift; i++) {
                    tmp->unshift(tmp->pop());
                }
            } else {
                for (Index i = 0; i < -shift; i++) {
                    tmp->push(tmp->shift());
                }
            }
        }
    
        {
            this->listrot_02_out1_set(tmp);
            return;
        }
    }
    
    void button_02_output_bang() {
        this->listrot_02_input_bang();
    }
    
    void button_02_bangval_bang() {
        this->getEngine()->sendBangMessage(
            TAG("bangout"),
            TAG("rotating_clock_divider/button_obj-57"),
            this->_currentTime
        );;
    
        this->button_02_output_bang();
    }
    
    void numberobj_02_output_set(number v) {
        this->listrot_02_shift_set(v);
        this->button_02_bangval_bang();
    }
    
    void numberobj_02_value_set(number v) {
        this->numberobj_02_value_setter(v);
        v = this->numberobj_02_value;
        number localvalue = v;
    
        if (this->numberobj_02_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("rotating_clock_divider/number_obj-66"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_02_output_set(localvalue);
    }
    
    void eventinlet_04_out1_number_set(number v) {
        this->numberobj_02_value_set(v);
    }
    
    void numberobj_02_value_bang() {
        number v = this->numberobj_02_value;
        number localvalue = v;
    
        if (this->numberobj_02_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("rotating_clock_divider/number_obj-66"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_02_output_set(localvalue);
    }
    
    void listrot_02_input_set(const list& input) {
        this->listrot_02_input = jsCreateListCopy(input);
        auto shift = this->listrot_02_shift;
        list tmp = jsCreateListCopy(input);
    
        if (tmp->length > 0) {
            if (shift > 0) {
                for (Index i = 0; i < shift; i++) {
                    tmp->unshift(tmp->pop());
                }
            } else {
                for (Index i = 0; i < -shift; i++) {
                    tmp->push(tmp->shift());
                }
            }
        }
    
        {
            this->listrot_02_out1_set(tmp);
            return;
        }
    }
    
    void message_06_out_set(const list& v) {
        this->listrot_02_input_set(v);
    }
    
    void message_06_trigger_bang() {
        this->message_06_out_set(this->message_06_set);
    }
    
    void loadbang_02_output_bang() {
        this->message_06_trigger_bang();
    }
    
    void message_06_set_set(const list& v) {
        this->message_06_set = jsCreateListCopy(v);
    
        this->getEngine()->sendListMessage(
            TAG("listout"),
            TAG("rotating_clock_divider/message_obj-53"),
            v,
            this->_currentTime
        );
    }
    
    void rate_tilde_05_perform(const Sample * phase, number multiplier, SampleValue * out1, Index n) {
        auto __rate_tilde_05_quant = this->rate_tilde_05_quant;
        auto __rate_tilde_05_currentPhase = this->rate_tilde_05_currentPhase;
        auto __rate_tilde_05_prev = this->rate_tilde_05_prev;
        auto __rate_tilde_05_diff = this->rate_tilde_05_diff;
        auto __rate_tilde_05_wantlock = this->rate_tilde_05_wantlock;
        auto __rate_tilde_05_invmult = this->rate_tilde_05_invmult;
        auto __rate_tilde_05_mult = this->rate_tilde_05_mult;
        Index i;
    
        for (i = 0; i < n; i++) {
            if (multiplier != __rate_tilde_05_mult && (bool)(!(bool)(rnbo_isnan(multiplier)))) {
                __rate_tilde_05_mult = multiplier;
                __rate_tilde_05_invmult = this->safediv(1.0, __rate_tilde_05_mult);
                __rate_tilde_05_wantlock = 1;
            }
    
            __rate_tilde_05_diff = phase[(Index)i] - __rate_tilde_05_prev;
    
            if (__rate_tilde_05_diff < -0.5) {
                __rate_tilde_05_diff += 1;
            } else if (__rate_tilde_05_diff > 0.5) {
                __rate_tilde_05_diff -= 1;
            }
    
            if ((bool)(__rate_tilde_05_wantlock)) {
                __rate_tilde_05_currentPhase = (phase[(Index)i] - this->quantize(phase[(Index)i], __rate_tilde_05_quant)) * __rate_tilde_05_invmult + this->quantize(phase[(Index)i], __rate_tilde_05_quant * __rate_tilde_05_mult);
                __rate_tilde_05_diff = 0;
                __rate_tilde_05_wantlock = 0;
            } else {
                __rate_tilde_05_currentPhase += __rate_tilde_05_diff * __rate_tilde_05_invmult;
            }
    
            if (__rate_tilde_05_currentPhase > 1.0 || __rate_tilde_05_currentPhase < -0.0) {
                __rate_tilde_05_currentPhase = __rate_tilde_05_currentPhase - rnbo_floor(__rate_tilde_05_currentPhase);
            }
    
            __rate_tilde_05_prev = phase[(Index)i];
            out1[(Index)i] = __rate_tilde_05_currentPhase;
            continue;
        }
    
        this->rate_tilde_05_mult = __rate_tilde_05_mult;
        this->rate_tilde_05_invmult = __rate_tilde_05_invmult;
        this->rate_tilde_05_wantlock = __rate_tilde_05_wantlock;
        this->rate_tilde_05_diff = __rate_tilde_05_diff;
        this->rate_tilde_05_prev = __rate_tilde_05_prev;
        this->rate_tilde_05_currentPhase = __rate_tilde_05_currentPhase;
    }
    
    void wrap_tilde_05_perform(const Sample * x, number low, number high, SampleValue * out1, Index n) {
        RNBO_UNUSED(high);
        RNBO_UNUSED(low);
        Index i;
    
        for (i = 0; i < n; i++) {
            number lo;
            number hi;
            lo = 0;
            hi = 1;
            number range = hi - lo;
    
            if (x[(Index)i] >= lo && x[(Index)i] < hi) {
                out1[(Index)i] = x[(Index)i];
                continue;
            }
    
            if (range <= 0.000000001) {
                out1[(Index)i] = lo;
                continue;
            }
    
            long numWraps = (long)(trunc((x[(Index)i] - lo) / range));
            numWraps = numWraps - ((x[(Index)i] < lo ? 1 : 0));
            number result = x[(Index)i] - range * numWraps;
    
            if (result >= hi) {
                out1[(Index)i] = result - range;
                continue;
            } else {
                out1[(Index)i] = result;
                continue;
            }
        }
    }
    
    void delta_tilde_05_perform(const Sample * x, SampleValue * out1, Index n) {
        auto __delta_tilde_05_prev = this->delta_tilde_05_prev;
        Index i;
    
        for (i = 0; i < n; i++) {
            number temp = (number)(x[(Index)i] - __delta_tilde_05_prev);
            __delta_tilde_05_prev = x[(Index)i];
            out1[(Index)i] = temp;
        }
    
        this->delta_tilde_05_prev = __delta_tilde_05_prev;
    }
    
    void dspexpr_11_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] < 0;//#map:_###_obj_###_:1
        }
    }
    
    void gen_06_perform(const Sample * in1, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            number counter_1 = 0;
            number counter_2 = 0;
            number counter_3 = 0;
            array<number, 3> result_1 = this->gen_06_counter_0_next(in1[(Index)i], 0, 0);
            counter_3 = result_1[2];
            counter_2 = result_1[1];
            counter_1 = result_1[0];
            number mod_4_2 = this->safemod(counter_1, 2);
            out1[(Index)i] = mod_4_2;
        }
    }
    
    void rate_tilde_06_perform(const Sample * phase, number multiplier, SampleValue * out1, Index n) {
        auto __rate_tilde_06_quant = this->rate_tilde_06_quant;
        auto __rate_tilde_06_currentPhase = this->rate_tilde_06_currentPhase;
        auto __rate_tilde_06_prev = this->rate_tilde_06_prev;
        auto __rate_tilde_06_diff = this->rate_tilde_06_diff;
        auto __rate_tilde_06_wantlock = this->rate_tilde_06_wantlock;
        auto __rate_tilde_06_invmult = this->rate_tilde_06_invmult;
        auto __rate_tilde_06_mult = this->rate_tilde_06_mult;
        Index i;
    
        for (i = 0; i < n; i++) {
            if (multiplier != __rate_tilde_06_mult && (bool)(!(bool)(rnbo_isnan(multiplier)))) {
                __rate_tilde_06_mult = multiplier;
                __rate_tilde_06_invmult = this->safediv(1.0, __rate_tilde_06_mult);
                __rate_tilde_06_wantlock = 1;
            }
    
            __rate_tilde_06_diff = phase[(Index)i] - __rate_tilde_06_prev;
    
            if (__rate_tilde_06_diff < -0.5) {
                __rate_tilde_06_diff += 1;
            } else if (__rate_tilde_06_diff > 0.5) {
                __rate_tilde_06_diff -= 1;
            }
    
            if ((bool)(__rate_tilde_06_wantlock)) {
                __rate_tilde_06_currentPhase = (phase[(Index)i] - this->quantize(phase[(Index)i], __rate_tilde_06_quant)) * __rate_tilde_06_invmult + this->quantize(phase[(Index)i], __rate_tilde_06_quant * __rate_tilde_06_mult);
                __rate_tilde_06_diff = 0;
                __rate_tilde_06_wantlock = 0;
            } else {
                __rate_tilde_06_currentPhase += __rate_tilde_06_diff * __rate_tilde_06_invmult;
            }
    
            if (__rate_tilde_06_currentPhase > 1.0 || __rate_tilde_06_currentPhase < -0.0) {
                __rate_tilde_06_currentPhase = __rate_tilde_06_currentPhase - rnbo_floor(__rate_tilde_06_currentPhase);
            }
    
            __rate_tilde_06_prev = phase[(Index)i];
            out1[(Index)i] = __rate_tilde_06_currentPhase;
            continue;
        }
    
        this->rate_tilde_06_mult = __rate_tilde_06_mult;
        this->rate_tilde_06_invmult = __rate_tilde_06_invmult;
        this->rate_tilde_06_wantlock = __rate_tilde_06_wantlock;
        this->rate_tilde_06_diff = __rate_tilde_06_diff;
        this->rate_tilde_06_prev = __rate_tilde_06_prev;
        this->rate_tilde_06_currentPhase = __rate_tilde_06_currentPhase;
    }
    
    void wrap_tilde_06_perform(const Sample * x, number low, number high, SampleValue * out1, Index n) {
        RNBO_UNUSED(high);
        RNBO_UNUSED(low);
        Index i;
    
        for (i = 0; i < n; i++) {
            number lo;
            number hi;
            lo = 0;
            hi = 1;
            number range = hi - lo;
    
            if (x[(Index)i] >= lo && x[(Index)i] < hi) {
                out1[(Index)i] = x[(Index)i];
                continue;
            }
    
            if (range <= 0.000000001) {
                out1[(Index)i] = lo;
                continue;
            }
    
            long numWraps = (long)(trunc((x[(Index)i] - lo) / range));
            numWraps = numWraps - ((x[(Index)i] < lo ? 1 : 0));
            number result = x[(Index)i] - range * numWraps;
    
            if (result >= hi) {
                out1[(Index)i] = result - range;
                continue;
            } else {
                out1[(Index)i] = result;
                continue;
            }
        }
    }
    
    void delta_tilde_06_perform(const Sample * x, SampleValue * out1, Index n) {
        auto __delta_tilde_06_prev = this->delta_tilde_06_prev;
        Index i;
    
        for (i = 0; i < n; i++) {
            number temp = (number)(x[(Index)i] - __delta_tilde_06_prev);
            __delta_tilde_06_prev = x[(Index)i];
            out1[(Index)i] = temp;
        }
    
        this->delta_tilde_06_prev = __delta_tilde_06_prev;
    }
    
    void dspexpr_12_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] < 0;//#map:_###_obj_###_:1
        }
    }
    
    void gen_07_perform(const Sample * in1, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            number counter_1 = 0;
            number counter_2 = 0;
            number counter_3 = 0;
            array<number, 3> result_1 = this->gen_07_counter_0_next(in1[(Index)i], 0, 0);
            counter_3 = result_1[2];
            counter_2 = result_1[1];
            counter_1 = result_1[0];
            number mod_4_2 = this->safemod(counter_1, 2);
            out1[(Index)i] = mod_4_2;
        }
    }
    
    void rate_tilde_07_perform(const Sample * phase, number multiplier, SampleValue * out1, Index n) {
        auto __rate_tilde_07_quant = this->rate_tilde_07_quant;
        auto __rate_tilde_07_currentPhase = this->rate_tilde_07_currentPhase;
        auto __rate_tilde_07_prev = this->rate_tilde_07_prev;
        auto __rate_tilde_07_diff = this->rate_tilde_07_diff;
        auto __rate_tilde_07_wantlock = this->rate_tilde_07_wantlock;
        auto __rate_tilde_07_invmult = this->rate_tilde_07_invmult;
        auto __rate_tilde_07_mult = this->rate_tilde_07_mult;
        Index i;
    
        for (i = 0; i < n; i++) {
            if (multiplier != __rate_tilde_07_mult && (bool)(!(bool)(rnbo_isnan(multiplier)))) {
                __rate_tilde_07_mult = multiplier;
                __rate_tilde_07_invmult = this->safediv(1.0, __rate_tilde_07_mult);
                __rate_tilde_07_wantlock = 1;
            }
    
            __rate_tilde_07_diff = phase[(Index)i] - __rate_tilde_07_prev;
    
            if (__rate_tilde_07_diff < -0.5) {
                __rate_tilde_07_diff += 1;
            } else if (__rate_tilde_07_diff > 0.5) {
                __rate_tilde_07_diff -= 1;
            }
    
            if ((bool)(__rate_tilde_07_wantlock)) {
                __rate_tilde_07_currentPhase = (phase[(Index)i] - this->quantize(phase[(Index)i], __rate_tilde_07_quant)) * __rate_tilde_07_invmult + this->quantize(phase[(Index)i], __rate_tilde_07_quant * __rate_tilde_07_mult);
                __rate_tilde_07_diff = 0;
                __rate_tilde_07_wantlock = 0;
            } else {
                __rate_tilde_07_currentPhase += __rate_tilde_07_diff * __rate_tilde_07_invmult;
            }
    
            if (__rate_tilde_07_currentPhase > 1.0 || __rate_tilde_07_currentPhase < -0.0) {
                __rate_tilde_07_currentPhase = __rate_tilde_07_currentPhase - rnbo_floor(__rate_tilde_07_currentPhase);
            }
    
            __rate_tilde_07_prev = phase[(Index)i];
            out1[(Index)i] = __rate_tilde_07_currentPhase;
            continue;
        }
    
        this->rate_tilde_07_mult = __rate_tilde_07_mult;
        this->rate_tilde_07_invmult = __rate_tilde_07_invmult;
        this->rate_tilde_07_wantlock = __rate_tilde_07_wantlock;
        this->rate_tilde_07_diff = __rate_tilde_07_diff;
        this->rate_tilde_07_prev = __rate_tilde_07_prev;
        this->rate_tilde_07_currentPhase = __rate_tilde_07_currentPhase;
    }
    
    void wrap_tilde_07_perform(const Sample * x, number low, number high, SampleValue * out1, Index n) {
        RNBO_UNUSED(high);
        RNBO_UNUSED(low);
        Index i;
    
        for (i = 0; i < n; i++) {
            number lo;
            number hi;
            lo = 0;
            hi = 1;
            number range = hi - lo;
    
            if (x[(Index)i] >= lo && x[(Index)i] < hi) {
                out1[(Index)i] = x[(Index)i];
                continue;
            }
    
            if (range <= 0.000000001) {
                out1[(Index)i] = lo;
                continue;
            }
    
            long numWraps = (long)(trunc((x[(Index)i] - lo) / range));
            numWraps = numWraps - ((x[(Index)i] < lo ? 1 : 0));
            number result = x[(Index)i] - range * numWraps;
    
            if (result >= hi) {
                out1[(Index)i] = result - range;
                continue;
            } else {
                out1[(Index)i] = result;
                continue;
            }
        }
    }
    
    void delta_tilde_07_perform(const Sample * x, SampleValue * out1, Index n) {
        auto __delta_tilde_07_prev = this->delta_tilde_07_prev;
        Index i;
    
        for (i = 0; i < n; i++) {
            number temp = (number)(x[(Index)i] - __delta_tilde_07_prev);
            __delta_tilde_07_prev = x[(Index)i];
            out1[(Index)i] = temp;
        }
    
        this->delta_tilde_07_prev = __delta_tilde_07_prev;
    }
    
    void dspexpr_13_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] < 0;//#map:_###_obj_###_:1
        }
    }
    
    void gen_08_perform(const Sample * in1, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            number counter_1 = 0;
            number counter_2 = 0;
            number counter_3 = 0;
            array<number, 3> result_1 = this->gen_08_counter_0_next(in1[(Index)i], 0, 0);
            counter_3 = result_1[2];
            counter_2 = result_1[1];
            counter_1 = result_1[0];
            number mod_4_2 = this->safemod(counter_1, 2);
            out1[(Index)i] = mod_4_2;
        }
    }
    
    void rate_tilde_08_perform(const Sample * phase, number multiplier, SampleValue * out1, Index n) {
        auto __rate_tilde_08_quant = this->rate_tilde_08_quant;
        auto __rate_tilde_08_currentPhase = this->rate_tilde_08_currentPhase;
        auto __rate_tilde_08_prev = this->rate_tilde_08_prev;
        auto __rate_tilde_08_diff = this->rate_tilde_08_diff;
        auto __rate_tilde_08_wantlock = this->rate_tilde_08_wantlock;
        auto __rate_tilde_08_invmult = this->rate_tilde_08_invmult;
        auto __rate_tilde_08_mult = this->rate_tilde_08_mult;
        Index i;
    
        for (i = 0; i < n; i++) {
            if (multiplier != __rate_tilde_08_mult && (bool)(!(bool)(rnbo_isnan(multiplier)))) {
                __rate_tilde_08_mult = multiplier;
                __rate_tilde_08_invmult = this->safediv(1.0, __rate_tilde_08_mult);
                __rate_tilde_08_wantlock = 1;
            }
    
            __rate_tilde_08_diff = phase[(Index)i] - __rate_tilde_08_prev;
    
            if (__rate_tilde_08_diff < -0.5) {
                __rate_tilde_08_diff += 1;
            } else if (__rate_tilde_08_diff > 0.5) {
                __rate_tilde_08_diff -= 1;
            }
    
            if ((bool)(__rate_tilde_08_wantlock)) {
                __rate_tilde_08_currentPhase = (phase[(Index)i] - this->quantize(phase[(Index)i], __rate_tilde_08_quant)) * __rate_tilde_08_invmult + this->quantize(phase[(Index)i], __rate_tilde_08_quant * __rate_tilde_08_mult);
                __rate_tilde_08_diff = 0;
                __rate_tilde_08_wantlock = 0;
            } else {
                __rate_tilde_08_currentPhase += __rate_tilde_08_diff * __rate_tilde_08_invmult;
            }
    
            if (__rate_tilde_08_currentPhase > 1.0 || __rate_tilde_08_currentPhase < -0.0) {
                __rate_tilde_08_currentPhase = __rate_tilde_08_currentPhase - rnbo_floor(__rate_tilde_08_currentPhase);
            }
    
            __rate_tilde_08_prev = phase[(Index)i];
            out1[(Index)i] = __rate_tilde_08_currentPhase;
            continue;
        }
    
        this->rate_tilde_08_mult = __rate_tilde_08_mult;
        this->rate_tilde_08_invmult = __rate_tilde_08_invmult;
        this->rate_tilde_08_wantlock = __rate_tilde_08_wantlock;
        this->rate_tilde_08_diff = __rate_tilde_08_diff;
        this->rate_tilde_08_prev = __rate_tilde_08_prev;
        this->rate_tilde_08_currentPhase = __rate_tilde_08_currentPhase;
    }
    
    void wrap_tilde_08_perform(const Sample * x, number low, number high, SampleValue * out1, Index n) {
        RNBO_UNUSED(high);
        RNBO_UNUSED(low);
        Index i;
    
        for (i = 0; i < n; i++) {
            number lo;
            number hi;
            lo = 0;
            hi = 1;
            number range = hi - lo;
    
            if (x[(Index)i] >= lo && x[(Index)i] < hi) {
                out1[(Index)i] = x[(Index)i];
                continue;
            }
    
            if (range <= 0.000000001) {
                out1[(Index)i] = lo;
                continue;
            }
    
            long numWraps = (long)(trunc((x[(Index)i] - lo) / range));
            numWraps = numWraps - ((x[(Index)i] < lo ? 1 : 0));
            number result = x[(Index)i] - range * numWraps;
    
            if (result >= hi) {
                out1[(Index)i] = result - range;
                continue;
            } else {
                out1[(Index)i] = result;
                continue;
            }
        }
    }
    
    void delta_tilde_08_perform(const Sample * x, SampleValue * out1, Index n) {
        auto __delta_tilde_08_prev = this->delta_tilde_08_prev;
        Index i;
    
        for (i = 0; i < n; i++) {
            number temp = (number)(x[(Index)i] - __delta_tilde_08_prev);
            __delta_tilde_08_prev = x[(Index)i];
            out1[(Index)i] = temp;
        }
    
        this->delta_tilde_08_prev = __delta_tilde_08_prev;
    }
    
    void dspexpr_14_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] < 0;//#map:_###_obj_###_:1
        }
    }
    
    void gen_09_perform(const Sample * in1, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            number counter_1 = 0;
            number counter_2 = 0;
            number counter_3 = 0;
            array<number, 3> result_1 = this->gen_09_counter_0_next(in1[(Index)i], 0, 0);
            counter_3 = result_1[2];
            counter_2 = result_1[1];
            counter_1 = result_1[0];
            number mod_4_2 = this->safemod(counter_1, 2);
            out1[(Index)i] = mod_4_2;
        }
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void numberobj_02_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_02_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_02_value = localvalue;
    }
    
    void numberobj_02_init() {
        this->numberobj_02_currentFormat = 6;
    
        this->getEngine()->sendNumMessage(
            TAG("setup"),
            TAG("rotating_clock_divider/number_obj-66"),
            1,
            this->_currentTime
        );
    }
    
    void numberobj_02_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_02_value;
    }
    
    void numberobj_02_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_02_value_set(preset["value"]);
    }
    
    array<number, 3> gen_06_counter_0_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        RNBO_UNUSED(reset);
        number carry_flag = 0;
    
        {
            this->gen_06_counter_0_count += a;
        }
    
        return {this->gen_06_counter_0_count, carry_flag, this->gen_06_counter_0_carry};
    }
    
    void gen_06_counter_0_init() {
        this->gen_06_counter_0_count = 0;
    }
    
    void gen_06_counter_0_reset() {
        this->gen_06_counter_0_carry = 0;
        this->gen_06_counter_0_count = 0;
    }
    
    void rate_tilde_05_reset() {
        this->rate_tilde_05_currentPhase = 0;
        this->rate_tilde_05_diff = 0;
        this->rate_tilde_05_prev = 0;
        this->rate_tilde_05_mult = 1;
        this->rate_tilde_05_invmult = 1;
        this->rate_tilde_05_wantlock = 1;
        this->rate_tilde_05_quant = 1;
    }
    
    void rate_tilde_05_dspsetup(bool force) {
        if ((bool)(this->rate_tilde_05_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->rate_tilde_05_reset();
        this->rate_tilde_05_setupDone = true;
    }
    
    void delta_tilde_05_reset() {
        this->delta_tilde_05_prev = 0;
    }
    
    void delta_tilde_05_dspsetup(bool force) {
        if ((bool)(this->delta_tilde_05_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->delta_tilde_05_reset();
        this->delta_tilde_05_setupDone = true;
    }
    
    void message_06_init() {
        this->message_06_set_set({1, 2, 3, 4, 5, 6, 7, 8});
    }
    
    number line_05_valueAtTime(number time) {
        return this->line_05_startValue + this->line_05_slope * (time - this->line_05_startTime);
    }
    
    void line_05_scheduleNext() {
        auto currentTime = this->currenttime();
        number nextTime = currentTime + this->line_05_grain;
        number nextValue;
    
        if (nextTime - this->line_05_startTime >= this->line_05__time || this->line_05_grain == 0) {
            nextTime = this->line_05_startTime + this->line_05__time;
            nextValue = this->line_05_currentTarget;
        } else {
            nextValue = this->line_05_valueAtTime(nextTime);
        }
    
        this->getEngine()->scheduleClockEventWithValue(this, 1964277200, nextTime - currentTime + this->_currentTime, nextValue);;
    }
    
    void line_05_startRamp(number target, MillisecondTime time) {
        auto currentTime = this->currenttime();
        this->line_05_startValue = this->line_05_valueAtTime(currentTime);
        this->line_05_startTime = currentTime;
        this->line_05_currentTarget = target;
        this->getEngine()->flushClockEvents(this, 1964277200, false);;
        number rise = target - this->line_05_startValue;
        this->line_05_slope = rise / time;
        this->line_05_scheduleNext();
    }
    
    bool line_05_isFinished(number value) {
        return value == this->line_05_currentTarget && this->currenttime() - this->line_05_startTime >= this->line_05__time;
    }
    
    void line_05_startPendingRamp() {
        if (this->line_05_pendingRamps->length < 2) {
            this->line_05_pendingRamps->length = 0;
            this->line_05__time = 0;
            this->line_05_time_set(0);
            this->line_05_end_bang();
            return;
        }
    
        if (this->line_05_pendingRamps->length > 1) {
            number target = this->line_05_pendingRamps->shift();
            this->line_05__time = this->line_05_pendingRamps->shift();
            this->line_05__time = (this->line_05__time < 0 ? 0 : this->line_05__time);
            this->line_05_startRamp(target, this->line_05__time);
        }
    }
    
    void message_07_init() {
        this->message_07_set_set({5});
    }
    
    array<number, 3> gen_07_counter_0_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        RNBO_UNUSED(reset);
        number carry_flag = 0;
    
        {
            this->gen_07_counter_0_count += a;
        }
    
        return {this->gen_07_counter_0_count, carry_flag, this->gen_07_counter_0_carry};
    }
    
    void gen_07_counter_0_init() {
        this->gen_07_counter_0_count = 0;
    }
    
    void gen_07_counter_0_reset() {
        this->gen_07_counter_0_carry = 0;
        this->gen_07_counter_0_count = 0;
    }
    
    void rate_tilde_06_reset() {
        this->rate_tilde_06_currentPhase = 0;
        this->rate_tilde_06_diff = 0;
        this->rate_tilde_06_prev = 0;
        this->rate_tilde_06_mult = 1;
        this->rate_tilde_06_invmult = 1;
        this->rate_tilde_06_wantlock = 1;
        this->rate_tilde_06_quant = 1;
    }
    
    void rate_tilde_06_dspsetup(bool force) {
        if ((bool)(this->rate_tilde_06_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->rate_tilde_06_reset();
        this->rate_tilde_06_setupDone = true;
    }
    
    void delta_tilde_06_reset() {
        this->delta_tilde_06_prev = 0;
    }
    
    void delta_tilde_06_dspsetup(bool force) {
        if ((bool)(this->delta_tilde_06_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->delta_tilde_06_reset();
        this->delta_tilde_06_setupDone = true;
    }
    
    number line_06_valueAtTime(number time) {
        return this->line_06_startValue + this->line_06_slope * (time - this->line_06_startTime);
    }
    
    void line_06_scheduleNext() {
        auto currentTime = this->currenttime();
        number nextTime = currentTime + this->line_06_grain;
        number nextValue;
    
        if (nextTime - this->line_06_startTime >= this->line_06__time || this->line_06_grain == 0) {
            nextTime = this->line_06_startTime + this->line_06__time;
            nextValue = this->line_06_currentTarget;
        } else {
            nextValue = this->line_06_valueAtTime(nextTime);
        }
    
        this->getEngine()->scheduleClockEventWithValue(this, 1592269969, nextTime - currentTime + this->_currentTime, nextValue);;
    }
    
    void line_06_startRamp(number target, MillisecondTime time) {
        auto currentTime = this->currenttime();
        this->line_06_startValue = this->line_06_valueAtTime(currentTime);
        this->line_06_startTime = currentTime;
        this->line_06_currentTarget = target;
        this->getEngine()->flushClockEvents(this, 1592269969, false);;
        number rise = target - this->line_06_startValue;
        this->line_06_slope = rise / time;
        this->line_06_scheduleNext();
    }
    
    bool line_06_isFinished(number value) {
        return value == this->line_06_currentTarget && this->currenttime() - this->line_06_startTime >= this->line_06__time;
    }
    
    void line_06_startPendingRamp() {
        if (this->line_06_pendingRamps->length < 2) {
            this->line_06_pendingRamps->length = 0;
            this->line_06__time = 0;
            this->line_06_time_set(0);
            this->line_06_end_bang();
            return;
        }
    
        if (this->line_06_pendingRamps->length > 1) {
            number target = this->line_06_pendingRamps->shift();
            this->line_06__time = this->line_06_pendingRamps->shift();
            this->line_06__time = (this->line_06__time < 0 ? 0 : this->line_06__time);
            this->line_06_startRamp(target, this->line_06__time);
        }
    }
    
    void message_08_init() {
        this->message_08_set_set({6});
    }
    
    array<number, 3> gen_08_counter_0_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        RNBO_UNUSED(reset);
        number carry_flag = 0;
    
        {
            this->gen_08_counter_0_count += a;
        }
    
        return {this->gen_08_counter_0_count, carry_flag, this->gen_08_counter_0_carry};
    }
    
    void gen_08_counter_0_init() {
        this->gen_08_counter_0_count = 0;
    }
    
    void gen_08_counter_0_reset() {
        this->gen_08_counter_0_carry = 0;
        this->gen_08_counter_0_count = 0;
    }
    
    void rate_tilde_07_reset() {
        this->rate_tilde_07_currentPhase = 0;
        this->rate_tilde_07_diff = 0;
        this->rate_tilde_07_prev = 0;
        this->rate_tilde_07_mult = 1;
        this->rate_tilde_07_invmult = 1;
        this->rate_tilde_07_wantlock = 1;
        this->rate_tilde_07_quant = 1;
    }
    
    void rate_tilde_07_dspsetup(bool force) {
        if ((bool)(this->rate_tilde_07_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->rate_tilde_07_reset();
        this->rate_tilde_07_setupDone = true;
    }
    
    void delta_tilde_07_reset() {
        this->delta_tilde_07_prev = 0;
    }
    
    void delta_tilde_07_dspsetup(bool force) {
        if ((bool)(this->delta_tilde_07_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->delta_tilde_07_reset();
        this->delta_tilde_07_setupDone = true;
    }
    
    number line_07_valueAtTime(number time) {
        return this->line_07_startValue + this->line_07_slope * (time - this->line_07_startTime);
    }
    
    void line_07_scheduleNext() {
        auto currentTime = this->currenttime();
        number nextTime = currentTime + this->line_07_grain;
        number nextValue;
    
        if (nextTime - this->line_07_startTime >= this->line_07__time || this->line_07_grain == 0) {
            nextTime = this->line_07_startTime + this->line_07__time;
            nextValue = this->line_07_currentTarget;
        } else {
            nextValue = this->line_07_valueAtTime(nextTime);
        }
    
        this->getEngine()->scheduleClockEventWithValue(this, 1220262738, nextTime - currentTime + this->_currentTime, nextValue);;
    }
    
    void line_07_startRamp(number target, MillisecondTime time) {
        auto currentTime = this->currenttime();
        this->line_07_startValue = this->line_07_valueAtTime(currentTime);
        this->line_07_startTime = currentTime;
        this->line_07_currentTarget = target;
        this->getEngine()->flushClockEvents(this, 1220262738, false);;
        number rise = target - this->line_07_startValue;
        this->line_07_slope = rise / time;
        this->line_07_scheduleNext();
    }
    
    bool line_07_isFinished(number value) {
        return value == this->line_07_currentTarget && this->currenttime() - this->line_07_startTime >= this->line_07__time;
    }
    
    void line_07_startPendingRamp() {
        if (this->line_07_pendingRamps->length < 2) {
            this->line_07_pendingRamps->length = 0;
            this->line_07__time = 0;
            this->line_07_time_set(0);
            this->line_07_end_bang();
            return;
        }
    
        if (this->line_07_pendingRamps->length > 1) {
            number target = this->line_07_pendingRamps->shift();
            this->line_07__time = this->line_07_pendingRamps->shift();
            this->line_07__time = (this->line_07__time < 0 ? 0 : this->line_07__time);
            this->line_07_startRamp(target, this->line_07__time);
        }
    }
    
    void message_09_init() {
        this->message_09_set_set({7});
    }
    
    array<number, 3> gen_09_counter_0_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        RNBO_UNUSED(reset);
        number carry_flag = 0;
    
        {
            this->gen_09_counter_0_count += a;
        }
    
        return {this->gen_09_counter_0_count, carry_flag, this->gen_09_counter_0_carry};
    }
    
    void gen_09_counter_0_init() {
        this->gen_09_counter_0_count = 0;
    }
    
    void gen_09_counter_0_reset() {
        this->gen_09_counter_0_carry = 0;
        this->gen_09_counter_0_count = 0;
    }
    
    void rate_tilde_08_reset() {
        this->rate_tilde_08_currentPhase = 0;
        this->rate_tilde_08_diff = 0;
        this->rate_tilde_08_prev = 0;
        this->rate_tilde_08_mult = 1;
        this->rate_tilde_08_invmult = 1;
        this->rate_tilde_08_wantlock = 1;
        this->rate_tilde_08_quant = 1;
    }
    
    void rate_tilde_08_dspsetup(bool force) {
        if ((bool)(this->rate_tilde_08_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->rate_tilde_08_reset();
        this->rate_tilde_08_setupDone = true;
    }
    
    void delta_tilde_08_reset() {
        this->delta_tilde_08_prev = 0;
    }
    
    void delta_tilde_08_dspsetup(bool force) {
        if ((bool)(this->delta_tilde_08_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->delta_tilde_08_reset();
        this->delta_tilde_08_setupDone = true;
    }
    
    number line_08_valueAtTime(number time) {
        return this->line_08_startValue + this->line_08_slope * (time - this->line_08_startTime);
    }
    
    void line_08_scheduleNext() {
        auto currentTime = this->currenttime();
        number nextTime = currentTime + this->line_08_grain;
        number nextValue;
    
        if (nextTime - this->line_08_startTime >= this->line_08__time || this->line_08_grain == 0) {
            nextTime = this->line_08_startTime + this->line_08__time;
            nextValue = this->line_08_currentTarget;
        } else {
            nextValue = this->line_08_valueAtTime(nextTime);
        }
    
        this->getEngine()->scheduleClockEventWithValue(this, 848255507, nextTime - currentTime + this->_currentTime, nextValue);;
    }
    
    void line_08_startRamp(number target, MillisecondTime time) {
        auto currentTime = this->currenttime();
        this->line_08_startValue = this->line_08_valueAtTime(currentTime);
        this->line_08_startTime = currentTime;
        this->line_08_currentTarget = target;
        this->getEngine()->flushClockEvents(this, 848255507, false);;
        number rise = target - this->line_08_startValue;
        this->line_08_slope = rise / time;
        this->line_08_scheduleNext();
    }
    
    bool line_08_isFinished(number value) {
        return value == this->line_08_currentTarget && this->currenttime() - this->line_08_startTime >= this->line_08__time;
    }
    
    void line_08_startPendingRamp() {
        if (this->line_08_pendingRamps->length < 2) {
            this->line_08_pendingRamps->length = 0;
            this->line_08__time = 0;
            this->line_08_time_set(0);
            this->line_08_end_bang();
            return;
        }
    
        if (this->line_08_pendingRamps->length > 1) {
            number target = this->line_08_pendingRamps->shift();
            this->line_08__time = this->line_08_pendingRamps->shift();
            this->line_08__time = (this->line_08__time < 0 ? 0 : this->line_08__time);
            this->line_08_startRamp(target, this->line_08__time);
        }
    }
    
    void message_10_init() {
        this->message_10_set_set({8});
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        numberobj_02_value = 0;
        numberobj_02_value_setter(numberobj_02_value);
        gen_06_in1 = 0;
        rate_tilde_05_phase = 0;
        rate_tilde_05_multiplier = 1;
        dspexpr_11_in1 = 0;
        dspexpr_11_in2 = 0;
        delta_tilde_05_x = 0;
        wrap_tilde_05_x = 0;
        wrap_tilde_05_low = 0;
        wrap_tilde_05_high = 1;
        unpack_02_out1 = 0;
        unpack_02_out2 = 0;
        unpack_02_out3 = 0;
        unpack_02_out4 = 0;
        unpack_02_out5 = 0;
        unpack_02_out6 = 0;
        unpack_02_out7 = 0;
        unpack_02_out8 = 0;
        listrot_02_shift = 0;
        line_05_time = 0;
        line_05_grain = 100;
        line_05_output = 0;
        gen_07_in1 = 0;
        rate_tilde_06_phase = 0;
        rate_tilde_06_multiplier = 1;
        dspexpr_12_in1 = 0;
        dspexpr_12_in2 = 0;
        delta_tilde_06_x = 0;
        wrap_tilde_06_x = 0;
        wrap_tilde_06_low = 0;
        wrap_tilde_06_high = 1;
        line_06_time = 0;
        line_06_grain = 100;
        line_06_output = 0;
        gen_08_in1 = 0;
        rate_tilde_07_phase = 0;
        rate_tilde_07_multiplier = 1;
        dspexpr_13_in1 = 0;
        dspexpr_13_in2 = 0;
        delta_tilde_07_x = 0;
        wrap_tilde_07_x = 0;
        wrap_tilde_07_low = 0;
        wrap_tilde_07_high = 1;
        line_07_time = 0;
        line_07_grain = 100;
        line_07_output = 0;
        gen_09_in1 = 0;
        rate_tilde_08_phase = 0;
        rate_tilde_08_multiplier = 1;
        dspexpr_14_in1 = 0;
        dspexpr_14_in2 = 0;
        delta_tilde_08_x = 0;
        wrap_tilde_08_x = 0;
        wrap_tilde_08_low = 0;
        wrap_tilde_08_high = 1;
        line_08_time = 0;
        line_08_grain = 100;
        line_08_output = 0;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        numberobj_02_currentFormat = 6;
        numberobj_02_lastValue = 0;
        gen_06_counter_0_carry = 0;
        gen_06_counter_0_count = 0;
        rate_tilde_05_currentPhase = 0;
        rate_tilde_05_diff = 0;
        rate_tilde_05_prev = 0;
        rate_tilde_05_mult = 1;
        rate_tilde_05_invmult = 1;
        rate_tilde_05_wantlock = 1;
        rate_tilde_05_quant = 1;
        rate_tilde_05_setupDone = false;
        delta_tilde_05_prev = 0;
        delta_tilde_05_setupDone = false;
        line_05_startTime = 0;
        line_05_startValue = 0;
        line_05_currentTarget = 0;
        line_05_slope = 0;
        line_05__time = 0;
        gen_07_counter_0_carry = 0;
        gen_07_counter_0_count = 0;
        rate_tilde_06_currentPhase = 0;
        rate_tilde_06_diff = 0;
        rate_tilde_06_prev = 0;
        rate_tilde_06_mult = 1;
        rate_tilde_06_invmult = 1;
        rate_tilde_06_wantlock = 1;
        rate_tilde_06_quant = 1;
        rate_tilde_06_setupDone = false;
        delta_tilde_06_prev = 0;
        delta_tilde_06_setupDone = false;
        line_06_startTime = 0;
        line_06_startValue = 0;
        line_06_currentTarget = 0;
        line_06_slope = 0;
        line_06__time = 0;
        gen_08_counter_0_carry = 0;
        gen_08_counter_0_count = 0;
        rate_tilde_07_currentPhase = 0;
        rate_tilde_07_diff = 0;
        rate_tilde_07_prev = 0;
        rate_tilde_07_mult = 1;
        rate_tilde_07_invmult = 1;
        rate_tilde_07_wantlock = 1;
        rate_tilde_07_quant = 1;
        rate_tilde_07_setupDone = false;
        delta_tilde_07_prev = 0;
        delta_tilde_07_setupDone = false;
        line_07_startTime = 0;
        line_07_startValue = 0;
        line_07_currentTarget = 0;
        line_07_slope = 0;
        line_07__time = 0;
        gen_09_counter_0_carry = 0;
        gen_09_counter_0_count = 0;
        rate_tilde_08_currentPhase = 0;
        rate_tilde_08_diff = 0;
        rate_tilde_08_prev = 0;
        rate_tilde_08_mult = 1;
        rate_tilde_08_invmult = 1;
        rate_tilde_08_wantlock = 1;
        rate_tilde_08_quant = 1;
        rate_tilde_08_setupDone = false;
        delta_tilde_08_prev = 0;
        delta_tilde_08_setupDone = false;
        line_08_startTime = 0;
        line_08_startValue = 0;
        line_08_currentTarget = 0;
        line_08_slope = 0;
        line_08__time = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number numberobj_02_value;
        number gen_06_in1;
        number rate_tilde_05_phase;
        number rate_tilde_05_multiplier;
        number dspexpr_11_in1;
        number dspexpr_11_in2;
        number delta_tilde_05_x;
        number wrap_tilde_05_x;
        number wrap_tilde_05_low;
        number wrap_tilde_05_high;
        number unpack_02_out1;
        number unpack_02_out2;
        number unpack_02_out3;
        number unpack_02_out4;
        number unpack_02_out5;
        number unpack_02_out6;
        number unpack_02_out7;
        number unpack_02_out8;
        list listrot_02_input;
        number listrot_02_shift;
        list message_06_set;
        list line_05_target;
        number line_05_time;
        number line_05_grain;
        number line_05_output;
        list message_07_set;
        number gen_07_in1;
        number rate_tilde_06_phase;
        number rate_tilde_06_multiplier;
        number dspexpr_12_in1;
        number dspexpr_12_in2;
        number delta_tilde_06_x;
        number wrap_tilde_06_x;
        number wrap_tilde_06_low;
        number wrap_tilde_06_high;
        list line_06_target;
        number line_06_time;
        number line_06_grain;
        number line_06_output;
        list message_08_set;
        number gen_08_in1;
        number rate_tilde_07_phase;
        number rate_tilde_07_multiplier;
        number dspexpr_13_in1;
        number dspexpr_13_in2;
        number delta_tilde_07_x;
        number wrap_tilde_07_x;
        number wrap_tilde_07_low;
        number wrap_tilde_07_high;
        list line_07_target;
        number line_07_time;
        number line_07_grain;
        number line_07_output;
        list message_09_set;
        number gen_09_in1;
        number rate_tilde_08_phase;
        number rate_tilde_08_multiplier;
        number dspexpr_14_in1;
        number dspexpr_14_in2;
        number delta_tilde_08_x;
        number wrap_tilde_08_x;
        number wrap_tilde_08_low;
        number wrap_tilde_08_high;
        list line_08_target;
        number line_08_time;
        number line_08_grain;
        number line_08_output;
        list message_10_set;
        MillisecondTime _currentTime;
        SampleIndex audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[2];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        Int numberobj_02_currentFormat;
        number numberobj_02_lastValue;
        int gen_06_counter_0_carry;
        number gen_06_counter_0_count;
        SampleValue rate_tilde_05_currentPhase;
        SampleValue rate_tilde_05_diff;
        SampleValue rate_tilde_05_prev;
        SampleValue rate_tilde_05_mult;
        SampleValue rate_tilde_05_invmult;
        int rate_tilde_05_wantlock;
        int rate_tilde_05_quant;
        bool rate_tilde_05_setupDone;
        number delta_tilde_05_prev;
        bool delta_tilde_05_setupDone;
        number line_05_startTime;
        number line_05_startValue;
        number line_05_currentTarget;
        number line_05_slope;
        number line_05__time;
        list line_05_pendingRamps;
        int gen_07_counter_0_carry;
        number gen_07_counter_0_count;
        SampleValue rate_tilde_06_currentPhase;
        SampleValue rate_tilde_06_diff;
        SampleValue rate_tilde_06_prev;
        SampleValue rate_tilde_06_mult;
        SampleValue rate_tilde_06_invmult;
        int rate_tilde_06_wantlock;
        int rate_tilde_06_quant;
        bool rate_tilde_06_setupDone;
        number delta_tilde_06_prev;
        bool delta_tilde_06_setupDone;
        number line_06_startTime;
        number line_06_startValue;
        number line_06_currentTarget;
        number line_06_slope;
        number line_06__time;
        list line_06_pendingRamps;
        int gen_08_counter_0_carry;
        number gen_08_counter_0_count;
        SampleValue rate_tilde_07_currentPhase;
        SampleValue rate_tilde_07_diff;
        SampleValue rate_tilde_07_prev;
        SampleValue rate_tilde_07_mult;
        SampleValue rate_tilde_07_invmult;
        int rate_tilde_07_wantlock;
        int rate_tilde_07_quant;
        bool rate_tilde_07_setupDone;
        number delta_tilde_07_prev;
        bool delta_tilde_07_setupDone;
        number line_07_startTime;
        number line_07_startValue;
        number line_07_currentTarget;
        number line_07_slope;
        number line_07__time;
        list line_07_pendingRamps;
        int gen_09_counter_0_carry;
        number gen_09_counter_0_count;
        SampleValue rate_tilde_08_currentPhase;
        SampleValue rate_tilde_08_diff;
        SampleValue rate_tilde_08_prev;
        SampleValue rate_tilde_08_mult;
        SampleValue rate_tilde_08_invmult;
        int rate_tilde_08_wantlock;
        int rate_tilde_08_quant;
        bool rate_tilde_08_setupDone;
        number delta_tilde_08_prev;
        bool delta_tilde_08_setupDone;
        number line_08_startTime;
        number line_08_startValue;
        number line_08_currentTarget;
        number line_08_slope;
        number line_08__time;
        list line_08_pendingRamps;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

rnbomatic()
{
}

~rnbomatic()
{
    delete this->p_02;
    delete this->p_03;
    delete this->p_04;
}

rnbomatic* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
    getEngine()->flushClockEvents(this, -871642103, false);
    getEngine()->flushClockEvents(this, 1935387534, false);
}

template <typename T> void listquicksort(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    if (l < h) {
        Int p = (Int)(this->listpartition(arr, sortindices, l, h, ascending));
        this->listquicksort(arr, sortindices, l, p - 1, ascending);
        this->listquicksort(arr, sortindices, p + 1, h, ascending);
    }
}

template <typename T> Int listpartition(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    number x = arr[(Index)h];
    Int i = (Int)(l - 1);

    for (Int j = (Int)(l); j <= h - 1; j++) {
        bool asc = (bool)((bool)(ascending) && arr[(Index)j] <= x);
        bool desc = (bool)((bool)(!(bool)(ascending)) && arr[(Index)j] >= x);

        if ((bool)(asc) || (bool)(desc)) {
            i++;
            this->listswapelements(arr, i, j);
            this->listswapelements(sortindices, i, j);
        }
    }

    i++;
    this->listswapelements(arr, i, h);
    this->listswapelements(sortindices, i, h);
    return i;
}

template <typename T> void listswapelements(T& arr, Int a, Int b) {
    auto tmp = arr[(Index)a];
    arr[(Index)a] = arr[(Index)b];
    arr[(Index)b] = tmp;
}

MillisecondTime currenttime() {
    return this->_currentTime;
}

inline number safediv(number num, number denom) {
    return (denom == 0.0 ? 0.0 : num / denom);
}

number tempo() {
    return this->getTopLevelPatcher()->globaltransport_getTempo(this->currenttime());
}

number hztobeats(number hz) {
    return this->safediv(this->tempo() * 8, hz * 480.);
}

number samplerate() {
    return this->sr;
}

number beattimeatsample(number offset) {
    return this->getTopLevelPatcher()->globaltransport_getBeatTimeAtSample(offset);
}

number transportatsample(SampleIndex sampleOffset) {
    return this->getTopLevelPatcher()->globaltransport_getStateAtSample(sampleOffset);
}

number safepow(number base, number exponent) {
    return fixnan(rnbo_pow(base, exponent));
}

number scale(
    number x,
    number lowin,
    number hiin,
    number lowout,
    number highout,
    number pow
) {
    auto inscale = this->safediv(1., hiin - lowin);
    number outdiff = highout - lowout;
    number value = (x - lowin) * inscale;

    if (pow != 1) {
        if (value > 0)
            value = this->safepow(value, pow);
        else
            value = -this->safepow(-value, pow);
    }

    value = value * outdiff + lowout;
    return value;
}

number tickstohz(number ticks) {
    return (number)1 / (ticks / (number)480 * this->safediv(60, this->tempo()));
}

number tickstoms(number ticks) {
    return ticks / (number)480 * this->safediv(60, this->tempo()) * 1000;
}

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
}

number maximum(number x, number y) {
    return (x < y ? y : x);
}

number mstobeats(number ms) {
    return ms * this->tempo() * 0.008 / (number)480;
}

MillisecondTime sampstoms(number samps) {
    return samps * 1000 / this->sr;
}

Index getNumMidiInputPorts() const {
    return 0;
}

void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}

Index getNumMidiOutputPorts() const {
    return 0;
}

void process(
    const SampleValue * const* inputs,
    Index numInputs,
    SampleValue * const* outputs,
    Index numOutputs,
    Index n
) {
    RNBO_UNUSED(numInputs);
    RNBO_UNUSED(inputs);
    this->vs = n;
    this->updateTime(this->getEngine()->getCurrentTime());
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
    SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    SampleValue * out3 = (numOutputs >= 3 && outputs[2] ? outputs[2] : this->dummyBuffer);
    SampleValue * out4 = (numOutputs >= 4 && outputs[3] ? outputs[3] : this->dummyBuffer);
    SampleValue * out5 = (numOutputs >= 5 && outputs[4] ? outputs[4] : this->dummyBuffer);
    SampleValue * out6 = (numOutputs >= 6 && outputs[5] ? outputs[5] : this->dummyBuffer);
    SampleValue * out7 = (numOutputs >= 7 && outputs[6] ? outputs[6] : this->dummyBuffer);
    SampleValue * out8 = (numOutputs >= 8 && outputs[7] ? outputs[7] : this->dummyBuffer);
    SampleValue * out9 = (numOutputs >= 9 && outputs[8] ? outputs[8] : this->dummyBuffer);
    SampleValue * out10 = (numOutputs >= 10 && outputs[9] ? outputs[9] : this->dummyBuffer);
    this->phasor_01_perform(this->phasor_01_freq, this->signals[0], n);
    this->signalsend_01_perform(this->signals[0], this->signals[1], n);
    this->signalreceive_01_perform(this->signals[1], this->signals[0], n);
    this->p_04_perform(this->signals[0], out7, out8, out9, out10, n);
    this->p_02_perform(this->signals[0], out3, out4, out5, out6, n);
    this->p_03_perform(this->zeroBuffer, this->dummyBuffer, n);
    this->intnum_tilde_01_perform(this->intnum_tilde_01_value, out1, n);
    this->intnum_tilde_02_perform(this->intnum_tilde_02_value, out2, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 2; i++) {
            this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
        }

        this->phasor_01_sigbuf = resizeSignal(this->phasor_01_sigbuf, this->maxvs, maxBlockSize);
        this->globaltransport_tempo = resizeSignal(this->globaltransport_tempo, this->maxvs, maxBlockSize);
        this->globaltransport_state = resizeSignal(this->globaltransport_state, this->maxvs, maxBlockSize);
        this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
        this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
        this->didAllocateSignals = true;
    }

    const bool sampleRateChanged = sampleRate != this->sr;
    const bool maxvsChanged = maxBlockSize != this->maxvs;
    const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;

    if (sampleRateChanged || maxvsChanged) {
        this->vs = maxBlockSize;
        this->maxvs = maxBlockSize;
        this->sr = sampleRate;
        this->invsr = 1 / sampleRate;
    }

    this->phasor_01_dspsetup(forceDSPSetup);
    this->globaltransport_dspsetup(forceDSPSetup);
    this->p_02->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_03->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_04->prepareToProcess(sampleRate, maxBlockSize, force);

    if (sampleRateChanged)
        this->onSampleRateChanged(sampleRate);
}

void setProbingTarget(MessageTag id) {
    switch (id) {
    default:
        {
        this->setProbingIndex(-1);
        break;
        }
    }
}

void setProbingIndex(ProbingIndex ) {}

Index getProbingChannels(MessageTag outletId) const {
    RNBO_UNUSED(outletId);
    return 0;
}

DataRef* getDataRef(DataRefIndex index)  {
    switch (index) {
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 0;
}

void fillDataRef(DataRefIndex , DataRef& ) {}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    this->p_02->processDataViewUpdate(index, time);
    this->p_03->processDataViewUpdate(index, time);
    this->p_04->processDataViewUpdate(index, time);
}

void initialize() {
    this->assign_defaults();
    this->setState();
    this->initializeObjects();
    this->allocateDataRefs();
    this->startup();
}

Index getIsMuted()  {
    return this->isMuted;
}

void setIsMuted(Index v)  {
    this->isMuted = v;
}

Index getPatcherSerial() const {
    return 0;
}

void getState(PatcherStateInterface& ) {}

void setState() {
    this->p_02 = new RNBOSubpatcher_3775();
    this->p_02->setEngineAndPatcher(this->getEngine(), this);
    this->p_02->initialize();
    this->p_02->setParameterOffset(this->getParameterOffset(this->p_02));
    this->p_03 = new RNBOSubpatcher_3776();
    this->p_03->setEngineAndPatcher(this->getEngine(), this);
    this->p_03->initialize();
    this->p_03->setParameterOffset(this->getParameterOffset(this->p_03));
    this->p_04 = new RNBOSubpatcher_3777();
    this->p_04->setEngineAndPatcher(this->getEngine(), this);
    this->p_04->initialize();
    this->p_04->setParameterOffset(this->getParameterOffset(this->p_04));
}

void getPreset(PatcherStateInterface& preset) {
    preset["__presetid"] = "rnbo";
    this->param_02_getPresetValue(getSubState(preset, "bpm"));
    this->param_03_getPresetValue(getSubState(preset, "master_clock_led"));
    this->param_04_getPresetValue(getSubState(preset, "hex_left"));
    this->param_05_getPresetValue(getSubState(preset, "hex_left_size"));
    this->param_06_getPresetValue(getSubState(preset, "slide_2"));
    this->param_07_getPresetValue(getSubState(preset, "slide_3"));
    this->param_08_getPresetValue(getSubState(preset, "slide_4"));
    this->param_09_getPresetValue(getSubState(preset, "slide_5"));
    this->param_10_getPresetValue(getSubState(preset, "switch_hex"));
    this->param_11_getPresetValue(getSubState(preset, "1_led_clock"));
    this->param_12_getPresetValue(getSubState(preset, "slide_6"));
    this->param_13_getPresetValue(getSubState(preset, "hex_right"));
    this->param_14_getPresetValue(getSubState(preset, "2_led_duff"));
    this->param_15_getPresetValue(getSubState(preset, "hex_right_size"));
    this->param_16_getPresetValue(getSubState(preset, "3_led_kps"));
    this->param_17_getPresetValue(getSubState(preset, "slide_7"));
    this->param_18_getPresetValue(getSubState(preset, "4_led_bw"));
    this->param_19_getPresetValue(getSubState(preset, "slide_8"));
    this->param_20_getPresetValue(getSubState(preset, "switch_slide"));
    this->param_21_getPresetValue(getSubState(preset, "5_led_gain"));
    this->param_22_getPresetValue(getSubState(preset, "6_led_skip"));
    this->param_23_getPresetValue(getSubState(preset, "7_led_eshp"));
    this->param_24_getPresetValue(getSubState(preset, "8_led_elght"));
    this->p_02->getPreset(getSubState(getSubState(preset, "__sps"), "rotating_clock_divider[1]"));
    this->p_03->getPreset(getSubState(getSubState(preset, "__sps"), "probability_skip[1]"));
    this->p_04->getPreset(getSubState(getSubState(preset, "__sps"), "rotating_clock_divider"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);
    this->param_02_setPresetValue(getSubState(preset, "bpm"));
    this->param_03_setPresetValue(getSubState(preset, "master_clock_led"));
    this->param_04_setPresetValue(getSubState(preset, "hex_left"));
    this->param_05_setPresetValue(getSubState(preset, "hex_left_size"));
    this->param_06_setPresetValue(getSubState(preset, "slide_2"));
    this->param_07_setPresetValue(getSubState(preset, "slide_3"));
    this->param_08_setPresetValue(getSubState(preset, "slide_4"));
    this->param_09_setPresetValue(getSubState(preset, "slide_5"));
    this->param_10_setPresetValue(getSubState(preset, "switch_hex"));
    this->param_11_setPresetValue(getSubState(preset, "1_led_clock"));
    this->param_12_setPresetValue(getSubState(preset, "slide_6"));
    this->param_13_setPresetValue(getSubState(preset, "hex_right"));
    this->param_14_setPresetValue(getSubState(preset, "2_led_duff"));
    this->param_15_setPresetValue(getSubState(preset, "hex_right_size"));
    this->param_16_setPresetValue(getSubState(preset, "3_led_kps"));
    this->param_17_setPresetValue(getSubState(preset, "slide_7"));
    this->param_18_setPresetValue(getSubState(preset, "4_led_bw"));
    this->param_19_setPresetValue(getSubState(preset, "slide_8"));
    this->param_20_setPresetValue(getSubState(preset, "switch_slide"));
    this->param_21_setPresetValue(getSubState(preset, "5_led_gain"));
    this->param_22_setPresetValue(getSubState(preset, "6_led_skip"));
    this->param_23_setPresetValue(getSubState(preset, "7_led_eshp"));
    this->param_24_setPresetValue(getSubState(preset, "8_led_elght"));

    this->p_02->param_01_setPresetValue(
        getSubState(getSubState(getSubState(preset, "__sps"), "rotating_clock_divider[1]"), "slide_1")
    );
}

void processTempoEvent(MillisecondTime time, Tempo tempo) {
    this->updateTime(time);

    if (this->globaltransport_setTempo(this->_currentTime, tempo, false)) {
        this->p_02->processTempoEvent(time, tempo);
        this->p_03->processTempoEvent(time, tempo);
        this->p_04->processTempoEvent(time, tempo);
        this->transport_01_onTempoChanged(tempo);
        this->timevalue_01_onTempoChanged(tempo);
        this->timevalue_02_onTempoChanged(tempo);
    }
}

void processTransportEvent(MillisecondTime time, TransportState state) {
    this->updateTime(time);

    if (this->globaltransport_setState(this->_currentTime, state, false)) {
        this->p_02->processTransportEvent(time, state);
        this->p_03->processTransportEvent(time, state);
        this->p_04->processTransportEvent(time, state);
        this->transport_01_onTransportChanged(state);
        this->metro_01_onTransportChanged(state);
    }
}

void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
    this->updateTime(time);

    if (this->globaltransport_setBeatTime(this->_currentTime, beattime, false)) {
        this->p_02->processBeatTimeEvent(time, beattime);
        this->p_03->processBeatTimeEvent(time, beattime);
        this->p_04->processBeatTimeEvent(time, beattime);
        this->metro_01_onBeatTimeChanged(beattime);
    }
}

void onSampleRateChanged(double samplerate) {
    this->timevalue_01_onSampleRateChanged(samplerate);
    this->timevalue_02_onSampleRateChanged(samplerate);
}

void processTimeSignatureEvent(MillisecondTime time, int numerator, int denominator) {
    this->updateTime(time);

    if (this->globaltransport_setTimeSignature(this->_currentTime, numerator, denominator, false)) {
        this->p_02->processTimeSignatureEvent(time, numerator, denominator);
        this->p_03->processTimeSignatureEvent(time, numerator, denominator);
        this->p_04->processTimeSignatureEvent(time, numerator, denominator);
        this->transport_01_onTimeSignatureChanged(numerator, denominator);
        this->timevalue_01_onTimeSignatureChanged(numerator, denominator);
        this->timevalue_02_onTimeSignatureChanged(numerator, denominator);
    }
}

void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
    this->updateTime(time);

    switch (index) {
    case 0:
        {
        this->param_02_value_set(v);
        break;
        }
    case 1:
        {
        this->param_03_value_set(v);
        break;
        }
    case 2:
        {
        this->param_04_value_set(v);
        break;
        }
    case 3:
        {
        this->param_05_value_set(v);
        break;
        }
    case 4:
        {
        this->param_06_value_set(v);
        break;
        }
    case 5:
        {
        this->param_07_value_set(v);
        break;
        }
    case 6:
        {
        this->param_08_value_set(v);
        break;
        }
    case 7:
        {
        this->param_09_value_set(v);
        break;
        }
    case 8:
        {
        this->param_10_value_set(v);
        break;
        }
    case 9:
        {
        this->param_11_value_set(v);
        break;
        }
    case 10:
        {
        this->param_12_value_set(v);
        break;
        }
    case 11:
        {
        this->param_13_value_set(v);
        break;
        }
    case 12:
        {
        this->param_14_value_set(v);
        break;
        }
    case 13:
        {
        this->param_15_value_set(v);
        break;
        }
    case 14:
        {
        this->param_16_value_set(v);
        break;
        }
    case 15:
        {
        this->param_17_value_set(v);
        break;
        }
    case 16:
        {
        this->param_18_value_set(v);
        break;
        }
    case 17:
        {
        this->param_19_value_set(v);
        break;
        }
    case 18:
        {
        this->param_20_value_set(v);
        break;
        }
    case 19:
        {
        this->param_21_value_set(v);
        break;
        }
    case 20:
        {
        this->param_22_value_set(v);
        break;
        }
    case 21:
        {
        this->param_23_value_set(v);
        break;
        }
    case 22:
        {
        this->param_24_value_set(v);
        break;
        }
    default:
        {
        index -= 23;

        if (index < this->p_02->getNumParameters())
            this->p_02->setParameterValue(index, v, time);

        index -= this->p_02->getNumParameters();

        if (index < this->p_03->getNumParameters())
            this->p_03->setParameterValue(index, v, time);

        index -= this->p_03->getNumParameters();

        if (index < this->p_04->getNumParameters())
            this->p_04->setParameterValue(index, v, time);

        break;
        }
    }
}

void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValue(index, value, time);
}

void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
    this->setParameterValue(index, this->getParameterValue(index), time);
}

void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValueNormalized(index, value, time);
}

ParameterValue getParameterValue(ParameterIndex index)  {
    switch (index) {
    case 0:
        {
        return this->param_02_value;
        }
    case 1:
        {
        return this->param_03_value;
        }
    case 2:
        {
        return this->param_04_value;
        }
    case 3:
        {
        return this->param_05_value;
        }
    case 4:
        {
        return this->param_06_value;
        }
    case 5:
        {
        return this->param_07_value;
        }
    case 6:
        {
        return this->param_08_value;
        }
    case 7:
        {
        return this->param_09_value;
        }
    case 8:
        {
        return this->param_10_value;
        }
    case 9:
        {
        return this->param_11_value;
        }
    case 10:
        {
        return this->param_12_value;
        }
    case 11:
        {
        return this->param_13_value;
        }
    case 12:
        {
        return this->param_14_value;
        }
    case 13:
        {
        return this->param_15_value;
        }
    case 14:
        {
        return this->param_16_value;
        }
    case 15:
        {
        return this->param_17_value;
        }
    case 16:
        {
        return this->param_18_value;
        }
    case 17:
        {
        return this->param_19_value;
        }
    case 18:
        {
        return this->param_20_value;
        }
    case 19:
        {
        return this->param_21_value;
        }
    case 20:
        {
        return this->param_22_value;
        }
    case 21:
        {
        return this->param_23_value;
        }
    case 22:
        {
        return this->param_24_value;
        }
    default:
        {
        index -= 23;

        if (index < this->p_02->getNumParameters())
            return this->p_02->getParameterValue(index);

        index -= this->p_02->getNumParameters();

        if (index < this->p_03->getNumParameters())
            return this->p_03->getParameterValue(index);

        index -= this->p_03->getNumParameters();

        if (index < this->p_04->getNumParameters())
            return this->p_04->getParameterValue(index);

        return 0;
        }
    }
}

ParameterIndex getNumSignalInParameters() const {
    return 0;
}

ParameterIndex getNumSignalOutParameters() const {
    return 0;
}

ParameterIndex getNumParameters() const {
    return 23 + this->p_02->getNumParameters() + this->p_03->getNumParameters() + this->p_04->getNumParameters();
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "bpm";
        }
    case 1:
        {
        return "master_clock_led";
        }
    case 2:
        {
        return "hex_left";
        }
    case 3:
        {
        return "hex_left_size";
        }
    case 4:
        {
        return "slide_2";
        }
    case 5:
        {
        return "slide_3";
        }
    case 6:
        {
        return "slide_4";
        }
    case 7:
        {
        return "slide_5";
        }
    case 8:
        {
        return "switch_hex";
        }
    case 9:
        {
        return "1_led_clock";
        }
    case 10:
        {
        return "slide_6";
        }
    case 11:
        {
        return "hex_right";
        }
    case 12:
        {
        return "2_led_duff";
        }
    case 13:
        {
        return "hex_right_size";
        }
    case 14:
        {
        return "3_led_kps";
        }
    case 15:
        {
        return "slide_7";
        }
    case 16:
        {
        return "4_led_bw";
        }
    case 17:
        {
        return "slide_8";
        }
    case 18:
        {
        return "switch_slide";
        }
    case 19:
        {
        return "5_led_gain";
        }
    case 20:
        {
        return "6_led_skip";
        }
    case 21:
        {
        return "7_led_eshp";
        }
    case 22:
        {
        return "8_led_elght";
        }
    default:
        {
        index -= 23;

        if (index < this->p_02->getNumParameters())
            return this->p_02->getParameterName(index);

        index -= this->p_02->getNumParameters();

        if (index < this->p_03->getNumParameters())
            return this->p_03->getParameterName(index);

        index -= this->p_03->getNumParameters();

        if (index < this->p_04->getNumParameters())
            return this->p_04->getParameterName(index);

        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "bpm";
        }
    case 1:
        {
        return "master_clock_led";
        }
    case 2:
        {
        return "hex_left";
        }
    case 3:
        {
        return "hex_left_size";
        }
    case 4:
        {
        return "slide_2";
        }
    case 5:
        {
        return "slide_3";
        }
    case 6:
        {
        return "slide_4";
        }
    case 7:
        {
        return "slide_5";
        }
    case 8:
        {
        return "switch_hex";
        }
    case 9:
        {
        return "1_led_clock";
        }
    case 10:
        {
        return "slide_6";
        }
    case 11:
        {
        return "hex_right";
        }
    case 12:
        {
        return "2_led_duff";
        }
    case 13:
        {
        return "hex_right_size";
        }
    case 14:
        {
        return "3_led_kps";
        }
    case 15:
        {
        return "slide_7";
        }
    case 16:
        {
        return "4_led_bw";
        }
    case 17:
        {
        return "slide_8";
        }
    case 18:
        {
        return "switch_slide";
        }
    case 19:
        {
        return "5_led_gain";
        }
    case 20:
        {
        return "6_led_skip";
        }
    case 21:
        {
        return "7_led_eshp";
        }
    case 22:
        {
        return "8_led_elght";
        }
    default:
        {
        index -= 23;

        if (index < this->p_02->getNumParameters())
            return this->p_02->getParameterId(index);

        index -= this->p_02->getNumParameters();

        if (index < this->p_03->getNumParameters())
            return this->p_03->getParameterId(index);

        index -= this->p_03->getNumParameters();

        if (index < this->p_04->getNumParameters())
            return this->p_04->getParameterId(index);

        return "bogus";
        }
    }
}

void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
    {
        switch (index) {
        case 0:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 1:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 2:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 3:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 4:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 5:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 6:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 7:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 8:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 9:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 10:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 11:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 12:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 13:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 14:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 15:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 16:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 17:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 18:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 19:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 20:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 21:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 22:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        default:
            {
            index -= 23;

            if (index < this->p_02->getNumParameters())
                this->p_02->getParameterInfo(index, info);

            index -= this->p_02->getNumParameters();

            if (index < this->p_03->getNumParameters())
                this->p_03->getParameterInfo(index, info);

            index -= this->p_03->getNumParameters();

            if (index < this->p_04->getNumParameters())
                this->p_04->getParameterInfo(index, info);

            break;
            }
        }
    }
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
    if (subpatcher == this->p_02)
        return 23;

    if (subpatcher == this->p_03)
        return 23 + this->p_02->getNumParameters();

    if (subpatcher == this->p_04)
        return 23 + this->p_02->getNumParameters() + this->p_03->getNumParameters();

    return 0;
}

ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
    if (steps == 1) {
        if (normalizedValue > 0) {
            normalizedValue = 1.;
        }
    } else {
        ParameterValue oneStep = (number)1. / (steps - 1);
        ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
        normalizedValue = numberOfSteps * oneStep;
    }

    return normalizedValue;
}

ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);
            return normalizedValue;
        }
        }
    default:
        {
        index -= 23;

        if (index < this->p_02->getNumParameters())
            return this->p_02->convertToNormalizedParameterValue(index, value);

        index -= this->p_02->getNumParameters();

        if (index < this->p_03->getNumParameters())
            return this->p_03->convertToNormalizedParameterValue(index, value);

        index -= this->p_03->getNumParameters();

        if (index < this->p_04->getNumParameters())
            return this->p_04->convertToNormalizedParameterValue(index, value);

        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (1 - 0);
            }
        }
        }
    default:
        {
        index -= 23;

        if (index < this->p_02->getNumParameters())
            return this->p_02->convertFromNormalizedParameterValue(index, value);

        index -= this->p_02->getNumParameters();

        if (index < this->p_03->getNumParameters())
            return this->p_03->convertFromNormalizedParameterValue(index, value);

        index -= this->p_03->getNumParameters();

        if (index < this->p_04->getNumParameters())
            return this->p_04->convertFromNormalizedParameterValue(index, value);

        return value;
        }
    }
}

ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
        {
        return this->param_02_value_constrain(value);
        }
    case 1:
        {
        return this->param_03_value_constrain(value);
        }
    case 2:
        {
        return this->param_04_value_constrain(value);
        }
    case 3:
        {
        return this->param_05_value_constrain(value);
        }
    case 4:
        {
        return this->param_06_value_constrain(value);
        }
    case 5:
        {
        return this->param_07_value_constrain(value);
        }
    case 6:
        {
        return this->param_08_value_constrain(value);
        }
    case 7:
        {
        return this->param_09_value_constrain(value);
        }
    case 8:
        {
        return this->param_10_value_constrain(value);
        }
    case 9:
        {
        return this->param_11_value_constrain(value);
        }
    case 10:
        {
        return this->param_12_value_constrain(value);
        }
    case 11:
        {
        return this->param_13_value_constrain(value);
        }
    case 12:
        {
        return this->param_14_value_constrain(value);
        }
    case 13:
        {
        return this->param_15_value_constrain(value);
        }
    case 14:
        {
        return this->param_16_value_constrain(value);
        }
    case 15:
        {
        return this->param_17_value_constrain(value);
        }
    case 16:
        {
        return this->param_18_value_constrain(value);
        }
    case 17:
        {
        return this->param_19_value_constrain(value);
        }
    case 18:
        {
        return this->param_20_value_constrain(value);
        }
    case 19:
        {
        return this->param_21_value_constrain(value);
        }
    case 20:
        {
        return this->param_22_value_constrain(value);
        }
    case 21:
        {
        return this->param_23_value_constrain(value);
        }
    case 22:
        {
        return this->param_24_value_constrain(value);
        }
    default:
        {
        index -= 23;

        if (index < this->p_02->getNumParameters())
            return this->p_02->constrainParameterValue(index, value);

        index -= this->p_02->getNumParameters();

        if (index < this->p_03->getNumParameters())
            return this->p_03->constrainParameterValue(index, value);

        index -= this->p_03->getNumParameters();

        if (index < this->p_04->getNumParameters())
            return this->p_04->constrainParameterValue(index, value);

        return value;
        }
    }
}

void scheduleParamInit(ParameterIndex index, Index order) {
    this->paramInitIndices->push(index);
    this->paramInitOrder->push(order);
}

void processParamInitEvents() {
    this->listquicksort(
        this->paramInitOrder,
        this->paramInitIndices,
        0,
        (int)(this->paramInitOrder->length - 1),
        true
    );

    for (Index i = 0; i < this->paramInitOrder->length; i++) {
        this->getEngine()->scheduleParameterBang(this->paramInitIndices[i], 0);
    }
}

void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
    RNBO_UNUSED(value);
    RNBO_UNUSED(hasValue);
    this->updateTime(time);

    switch (index) {
    case -871642103:
        {
        this->loadbang_03_startupbang_bang();
        break;
        }
    case 1935387534:
        {
        this->metro_01_tick_bang();
        break;
        }
    }
}

void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}

void processOutletEvent(
    EngineLink* sender,
    OutletIndex index,
    ParameterValue value,
    MillisecondTime time
) {
    this->updateTime(time);
    this->processOutletAtCurrentTime(sender, index, value);
}

void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
    this->updateTime(time);

    switch (tag) {
    case TAG("valin"):
        {
        if (TAG("toggle_obj-37") == objectId)
            this->toggle_01_valin_set(payload);

        if (TAG("toggle_obj-42") == objectId)
            this->toggle_02_valin_set(payload);

        if (TAG("toggle_obj-383") == objectId)
            this->toggle_03_valin_set(payload);

        if (TAG("toggle_obj-384") == objectId)
            this->toggle_04_valin_set(payload);

        if (TAG("toggle_obj-390") == objectId)
            this->toggle_05_valin_set(payload);

        if (TAG("toggle_obj-387") == objectId)
            this->toggle_06_valin_set(payload);

        if (TAG("toggle_obj-17") == objectId)
            this->toggle_07_valin_set(payload);

        if (TAG("toggle_obj-16") == objectId)
            this->toggle_08_valin_set(payload);

        if (TAG("toggle_obj-15") == objectId)
            this->toggle_09_valin_set(payload);

        if (TAG("toggle_obj-14") == objectId)
            this->toggle_10_valin_set(payload);

        break;
        }
    case TAG("listin"):
        {
        if (TAG("message_obj-427") == objectId)
            this->message_11_listin_number_set(payload);

        break;
        }
    }

    this->p_02->processNumMessage(tag, objectId, time, payload);
    this->p_03->processNumMessage(tag, objectId, time, payload);
    this->p_04->processNumMessage(tag, objectId, time, payload);
}

void processListMessage(
    MessageTag tag,
    MessageTag objectId,
    MillisecondTime time,
    const list& payload
) {
    this->updateTime(time);

    switch (tag) {
    case TAG("listin"):
        {
        if (TAG("message_obj-427") == objectId)
            this->message_11_listin_list_set(payload);

        break;
        }
    }

    this->p_02->processListMessage(tag, objectId, time, payload);
    this->p_03->processListMessage(tag, objectId, time, payload);
    this->p_04->processListMessage(tag, objectId, time, payload);
}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    this->updateTime(time);

    switch (tag) {
    case TAG("startupbang"):
        {
        if (TAG("loadbang_obj-36") == objectId)
            this->loadbang_03_startupbang_bang();

        break;
        }
    case TAG("bangin"):
        {
        if (TAG("button_obj-54") == objectId)
            this->button_03_bangin_bang();

        break;
        }
    case TAG("listin"):
        {
        if (TAG("message_obj-427") == objectId)
            this->message_11_listin_bang_bang();

        break;
        }
    }

    this->p_02->processBangMessage(tag, objectId, time);
    this->p_03->processBangMessage(tag, objectId, time);
    this->p_04->processBangMessage(tag, objectId, time);
}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {
    case TAG("valout"):
        {
        return "valout";
        }
    case TAG("toggle_obj-37"):
        {
        return "toggle_obj-37";
        }
    case TAG("bangout"):
        {
        return "bangout";
        }
    case TAG("button_obj-54"):
        {
        return "button_obj-54";
        }
    case TAG("toggle_obj-42"):
        {
        return "toggle_obj-42";
        }
    case TAG("listout"):
        {
        return "listout";
        }
    case TAG("message_obj-427"):
        {
        return "message_obj-427";
        }
    case TAG("master_clock"):
        {
        return "master_clock";
        }
    case TAG(""):
        {
        return "";
        }
    case TAG("toggle_obj-383"):
        {
        return "toggle_obj-383";
        }
    case TAG("toggle_obj-384"):
        {
        return "toggle_obj-384";
        }
    case TAG("toggle_obj-390"):
        {
        return "toggle_obj-390";
        }
    case TAG("toggle_obj-387"):
        {
        return "toggle_obj-387";
        }
    case TAG("toggle_obj-17"):
        {
        return "toggle_obj-17";
        }
    case TAG("toggle_obj-16"):
        {
        return "toggle_obj-16";
        }
    case TAG("toggle_obj-15"):
        {
        return "toggle_obj-15";
        }
    case TAG("toggle_obj-14"):
        {
        return "toggle_obj-14";
        }
    case TAG("startupbang"):
        {
        return "startupbang";
        }
    case TAG("loadbang_obj-36"):
        {
        return "loadbang_obj-36";
        }
    case TAG("valin"):
        {
        return "valin";
        }
    case TAG("bangin"):
        {
        return "bangin";
        }
    case TAG("listin"):
        {
        return "listin";
        }
    }

    auto subpatchResult_0 = this->p_02->resolveTag(tag);

    if (subpatchResult_0)
        return subpatchResult_0;

    auto subpatchResult_1 = this->p_03->resolveTag(tag);

    if (subpatchResult_1)
        return subpatchResult_1;

    auto subpatchResult_2 = this->p_04->resolveTag(tag);

    if (subpatchResult_2)
        return subpatchResult_2;

    return "";
}

MessageIndex getNumMessages() const {
    return 1;
}

const MessageInfo& getMessageInfo(MessageIndex index) const {
    switch (index) {
    case 0:
        {
        static const MessageInfo r0 = {
            "master_clock",
            Outport
        };

        return r0;
        }
    }

    return NullMessageInfo;
}

protected:

void param_02_value_set(number v) {
    v = this->param_02_value_constrain(v);
    this->param_02_value = v;
    this->sendParameter(0, false);

    if (this->param_02_value != this->param_02_lastValue) {
        this->getEngine()->presetTouched();
        this->param_02_lastValue = this->param_02_value;
    }

    {
        list converted = {v};
        this->scale_01_input_set(converted);
    }
}

void param_03_value_set(number v) {
    v = this->param_03_value_constrain(v);
    this->param_03_value = v;
    this->sendParameter(1, false);

    if (this->param_03_value != this->param_03_lastValue) {
        this->getEngine()->presetTouched();
        this->param_03_lastValue = this->param_03_value;
    }
}

void param_04_value_set(number v) {
    v = this->param_04_value_constrain(v);
    this->param_04_value = v;
    this->sendParameter(2, false);

    if (this->param_04_value != this->param_04_lastValue) {
        this->getEngine()->presetTouched();
        this->param_04_lastValue = this->param_04_value;
    }

    this->latch_01_x_set(v);
}

void param_05_value_set(number v) {
    v = this->param_05_value_constrain(v);
    this->param_05_value = v;
    this->sendParameter(3, false);

    if (this->param_05_value != this->param_05_lastValue) {
        this->getEngine()->presetTouched();
        this->param_05_lastValue = this->param_05_value;
    }

    this->expr_06_in1_set(v);
}

void param_06_value_set(number v) {
    v = this->param_06_value_constrain(v);
    this->param_06_value = v;
    this->sendParameter(4, false);

    if (this->param_06_value != this->param_06_lastValue) {
        this->getEngine()->presetTouched();
        this->param_06_lastValue = this->param_06_value;
    }
}

void param_07_value_set(number v) {
    v = this->param_07_value_constrain(v);
    this->param_07_value = v;
    this->sendParameter(5, false);

    if (this->param_07_value != this->param_07_lastValue) {
        this->getEngine()->presetTouched();
        this->param_07_lastValue = this->param_07_value;
    }
}

void param_08_value_set(number v) {
    v = this->param_08_value_constrain(v);
    this->param_08_value = v;
    this->sendParameter(6, false);

    if (this->param_08_value != this->param_08_lastValue) {
        this->getEngine()->presetTouched();
        this->param_08_lastValue = this->param_08_value;
    }
}

void param_09_value_set(number v) {
    v = this->param_09_value_constrain(v);
    this->param_09_value = v;
    this->sendParameter(7, false);

    if (this->param_09_value != this->param_09_lastValue) {
        this->getEngine()->presetTouched();
        this->param_09_lastValue = this->param_09_value;
    }
}

void param_10_value_set(number v) {
    v = this->param_10_value_constrain(v);
    this->param_10_value = v;
    this->sendParameter(8, false);

    if (this->param_10_value != this->param_10_lastValue) {
        this->getEngine()->presetTouched();
        this->param_10_lastValue = this->param_10_value;
    }

    this->select_01_input_number_set(v);
}

void param_12_value_set(number v) {
    v = this->param_12_value_constrain(v);
    this->param_12_value = v;
    this->sendParameter(10, false);

    if (this->param_12_value != this->param_12_lastValue) {
        this->getEngine()->presetTouched();
        this->param_12_lastValue = this->param_12_value;
    }
}

void param_13_value_set(number v) {
    v = this->param_13_value_constrain(v);
    this->param_13_value = v;
    this->sendParameter(11, false);

    if (this->param_13_value != this->param_13_lastValue) {
        this->getEngine()->presetTouched();
        this->param_13_lastValue = this->param_13_value;
    }

    this->latch_02_x_set(v);
}

void param_15_value_set(number v) {
    v = this->param_15_value_constrain(v);
    this->param_15_value = v;
    this->sendParameter(13, false);

    if (this->param_15_value != this->param_15_lastValue) {
        this->getEngine()->presetTouched();
        this->param_15_lastValue = this->param_15_value;
    }

    this->expr_08_in1_set(v);
}

void param_17_value_set(number v) {
    v = this->param_17_value_constrain(v);
    this->param_17_value = v;
    this->sendParameter(15, false);

    if (this->param_17_value != this->param_17_lastValue) {
        this->getEngine()->presetTouched();
        this->param_17_lastValue = this->param_17_value;
    }
}

void param_19_value_set(number v) {
    v = this->param_19_value_constrain(v);
    this->param_19_value = v;
    this->sendParameter(17, false);

    if (this->param_19_value != this->param_19_lastValue) {
        this->getEngine()->presetTouched();
        this->param_19_lastValue = this->param_19_value;
    }
}

void param_20_value_set(number v) {
    v = this->param_20_value_constrain(v);
    this->param_20_value = v;
    this->sendParameter(18, false);

    if (this->param_20_value != this->param_20_lastValue) {
        this->getEngine()->presetTouched();
        this->param_20_lastValue = this->param_20_value;
    }

    this->select_07_input_number_set(v);
}

void loadbang_03_startupbang_bang() {
    this->loadbang_03_output_bang();
}

void toggle_01_valin_set(number v) {
    this->toggle_01_value_number_set(v);
}

void button_03_bangin_bang() {
    this->button_03_bangval_bang();
}

void metro_01_tick_bang() {
    this->metro_01_tickout_bang();
    this->getEngine()->flushClockEvents(this, 1935387534, false);;

    if ((bool)(this->metro_01_on)) {
        this->metro_01_last = this->currenttime();

        {
            this->metro_01_next = this->metro_01_last + this->metro_01_interval;
            this->getEngine()->scheduleClockEvent(this, 1935387534, this->metro_01_interval + this->_currentTime);;
        }
    }
}

void toggle_02_valin_set(number v) {
    this->toggle_02_value_number_set(v);
}

void message_11_listin_list_set(const list& v) {
    this->message_11_set_set(v);
}

void message_11_listin_number_set(number v) {
    this->message_11_set_set(v);
}

void message_11_listin_bang_bang() {
    this->message_11_trigger_bang();
}

void toggle_03_valin_set(number v) {
    this->toggle_03_value_number_set(v);
}

void toggle_04_valin_set(number v) {
    this->toggle_04_value_number_set(v);
}

void toggle_05_valin_set(number v) {
    this->toggle_05_value_number_set(v);
}

void toggle_06_valin_set(number v) {
    this->toggle_06_value_number_set(v);
}

void toggle_07_valin_set(number v) {
    this->toggle_07_value_number_set(v);
}

void toggle_08_valin_set(number v) {
    this->toggle_08_value_number_set(v);
}

void toggle_09_valin_set(number v) {
    this->toggle_09_value_number_set(v);
}

void toggle_10_valin_set(number v) {
    this->toggle_10_value_number_set(v);
}

number msToSamps(MillisecondTime ms, number sampleRate) {
    return ms * sampleRate * 0.001;
}

MillisecondTime sampsToMs(SampleIndex samps) {
    return samps * (this->invsr * 1000);
}

Index getMaxBlockSize() const {
    return this->maxvs;
}

number getSampleRate() const {
    return this->sr;
}

bool hasFixedVectorSize() const {
    return false;
}

Index getNumInputChannels() const {
    return 0;
}

Index getNumOutputChannels() const {
    return 10;
}

void allocateDataRefs() {
    this->p_02->allocateDataRefs();
    this->p_03->allocateDataRefs();
    this->p_04->allocateDataRefs();
}

void initializeObjects() {
    this->message_11_init();
    this->p_02->initializeObjects();
    this->p_03->initializeObjects();
    this->p_04->initializeObjects();
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime());
    this->p_02->startup();
    this->p_03->startup();
    this->p_04->startup();
    this->getEngine()->scheduleClockEvent(this, -871642103, 0 + this->_currentTime);;

    if ((bool)(this->metro_01_on))
        this->metro_01_on_set(1);

    this->timevalue_01_sendValue();
    this->timevalue_02_sendValue();

    {
        this->scheduleParamInit(0, 0);
    }

    {
        this->scheduleParamInit(1, 0);
    }

    {
        this->scheduleParamInit(2, 0);
    }

    {
        this->scheduleParamInit(3, 0);
    }

    {
        this->scheduleParamInit(4, 0);
    }

    {
        this->scheduleParamInit(5, 0);
    }

    {
        this->scheduleParamInit(6, 0);
    }

    {
        this->scheduleParamInit(7, 0);
    }

    {
        this->scheduleParamInit(8, 0);
    }

    {
        this->scheduleParamInit(9, 0);
    }

    {
        this->scheduleParamInit(10, 0);
    }

    {
        this->scheduleParamInit(11, 0);
    }

    {
        this->scheduleParamInit(12, 0);
    }

    {
        this->scheduleParamInit(13, 0);
    }

    {
        this->scheduleParamInit(14, 0);
    }

    {
        this->scheduleParamInit(15, 0);
    }

    {
        this->scheduleParamInit(16, 0);
    }

    {
        this->scheduleParamInit(17, 0);
    }

    {
        this->scheduleParamInit(18, 0);
    }

    {
        this->scheduleParamInit(19, 0);
    }

    {
        this->scheduleParamInit(20, 0);
    }

    {
        this->scheduleParamInit(21, 0);
    }

    {
        this->scheduleParamInit(22, 0);
    }

    this->processParamInitEvents();
}

static number param_02_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void transport_01_tempo_set(number v) {
    this->transport_01_tempo = v;

    if (v >= 0) {
        this->getTopLevelPatcher()->globaltransport_setTempo(this->currenttime(), v, true);
    }
}

void scale_01_out_set(const list& v) {
    this->scale_01_out = jsCreateListCopy(v);

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->transport_01_tempo_set(converted);
    }
}

void scale_01_input_set(const list& v) {
    this->scale_01_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_01_inlow,
            this->scale_01_inhigh,
            this->scale_01_outlow,
            this->scale_01_outhigh,
            this->scale_01_power
        ));
    }

    this->scale_01_out_set(tmp);
}

static number param_03_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

static number param_04_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void p_02_in2_number_set(number v) {
    this->p_02->updateTime(this->_currentTime);
    this->p_02->eventinlet_02_out1_number_set(v);
}

void expr_05_out1_set(number v) {
    this->expr_05_out1 = v;
    this->p_02_in2_number_set(this->expr_05_out1);
}

void expr_05_in1_set(number in1) {
    this->expr_05_in1 = in1;

    this->expr_05_out1_set(
        (this->expr_05_in2 == 0 ? 0 : rnbo_fround((this->expr_05_in2 == 0. ? 0. : this->expr_05_in1 * 1 / this->expr_05_in2)) * this->expr_05_in2)
    );//#map:round_obj-92:1
}

void expr_05_in2_set(number v) {
    this->expr_05_in2 = v;
}

void scale_02_out_set(const list& v) {
    this->scale_02_out = jsCreateListCopy(v);

    {
        if (v->length > 1)
            this->expr_05_in2_set(v[1]);

        number converted = (v->length > 0 ? v[0] : 0);
        this->expr_05_in1_set(converted);
    }
}

void scale_02_input_set(const list& v) {
    this->scale_02_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_02_inlow,
            this->scale_02_inhigh,
            this->scale_02_outlow,
            this->scale_02_outhigh,
            this->scale_02_power
        ));
    }

    this->scale_02_out_set(tmp);
}

void latch_01_out1_set(number v) {
    {
        list converted = {v};
        this->scale_02_input_set(converted);
    }
}

void latch_01_x_set(number x) {
    this->latch_01_x = x;
    auto control = this->latch_01_control;

    if (control != 0.)
        this->latch_01_value = x;

    {
        this->latch_01_out1_set(this->latch_01_value);
        return;
    }
}

static number param_05_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void latch_01_control_set(number v) {
    this->latch_01_control = v;
}

void expr_06_out1_set(number v) {
    this->expr_06_out1 = v;
    this->latch_01_control_set(this->expr_06_out1);
}

void expr_06_in1_set(number in1) {
    this->expr_06_in1 = in1;
    this->expr_06_out1_set(this->expr_06_in1 >= this->expr_06_in2);//#map:>=_obj-81:1
}

static number param_06_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

static number param_07_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

static number param_08_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

static number param_09_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

static number param_10_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void select_02_match1_bang() {}

static number param_11_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void param_11_value_set(number v) {
    v = this->param_11_value_constrain(v);
    this->param_11_value = v;
    this->sendParameter(9, false);

    if (this->param_11_value != this->param_11_lastValue) {
        this->getEngine()->presetTouched();
        this->param_11_lastValue = this->param_11_value;
    }
}

static number param_18_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void param_18_value_set(number v) {
    v = this->param_18_value_constrain(v);
    this->param_18_value = v;
    this->sendParameter(16, false);

    if (this->param_18_value != this->param_18_lastValue) {
        this->getEngine()->presetTouched();
        this->param_18_lastValue = this->param_18_value;
    }
}

static number param_16_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void param_16_value_set(number v) {
    v = this->param_16_value_constrain(v);
    this->param_16_value = v;
    this->sendParameter(14, false);

    if (this->param_16_value != this->param_16_lastValue) {
        this->getEngine()->presetTouched();
        this->param_16_lastValue = this->param_16_value;
    }
}

void toggle_06_value_number_set(number v) {
    if (this->stackprotect_check())
        return;

    this->toggle_06_value_number_setter(v);
    v = this->toggle_06_value_number;
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("toggle_obj-387"), v, this->_currentTime);
    this->toggle_06_output_set(v);
}

static number param_14_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void param_14_value_set(number v) {
    v = this->param_14_value_constrain(v);
    this->param_14_value = v;
    this->sendParameter(12, false);

    if (this->param_14_value != this->param_14_lastValue) {
        this->getEngine()->presetTouched();
        this->param_14_lastValue = this->param_14_value;
    }
}

void toggle_05_value_number_set(number v) {
    if (this->stackprotect_check())
        return;

    this->toggle_05_value_number_setter(v);
    v = this->toggle_05_value_number;
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("toggle_obj-390"), v, this->_currentTime);
    this->toggle_05_output_set(v);
}

void toggle_03_value_number_set(number v) {
    if (this->stackprotect_check())
        return;

    this->toggle_03_value_number_setter(v);
    v = this->toggle_03_value_number;
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("toggle_obj-383"), v, this->_currentTime);
    this->toggle_03_output_set(v);
}

void trigger_03_out2_set(number v) {
    this->toggle_06_value_number_set(v);
    this->toggle_05_value_number_set(v);
    this->toggle_03_value_number_set(v);
}

void trigger_03_out1_set(number ) {}

void trigger_03_input_bang_bang() {
    this->trigger_03_out2_set(0);
    this->trigger_03_out1_set(1);
}

void select_04_match1_bang() {
    this->trigger_03_input_bang_bang();
}

void select_04_nomatch_number_set(number ) {}

void select_04_input_number_set(number v) {
    if (v == this->select_04_test1)
        this->select_04_match1_bang();
    else
        this->select_04_nomatch_number_set(v);
}

void toggle_04_output_set(number v) {
    this->param_14_value_set(v);
    this->select_04_input_number_set(v);
}

void toggle_04_value_number_set(number v) {
    this->toggle_04_value_number_setter(v);
    v = this->toggle_04_value_number;
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("toggle_obj-384"), v, this->_currentTime);
    this->toggle_04_output_set(v);
}

void trigger_04_out2_set(number v) {
    this->toggle_06_value_number_set(v);
    this->toggle_04_value_number_set(v);
    this->toggle_03_value_number_set(v);
}

void trigger_04_out1_set(number ) {}

void trigger_04_input_bang_bang() {
    this->trigger_04_out2_set(0);
    this->trigger_04_out1_set(1);
}

void select_05_match1_bang() {
    this->trigger_04_input_bang_bang();
}

void select_05_nomatch_number_set(number ) {}

void select_05_input_number_set(number v) {
    if (v == this->select_05_test1)
        this->select_05_match1_bang();
    else
        this->select_05_nomatch_number_set(v);
}

void toggle_05_output_set(number v) {
    this->param_16_value_set(v);
    this->select_05_input_number_set(v);
}

void trigger_05_out2_set(number v) {
    this->toggle_05_value_number_set(v);
    this->toggle_04_value_number_set(v);
    this->toggle_03_value_number_set(v);
}

void trigger_05_out1_set(number ) {}

void trigger_05_input_bang_bang() {
    this->trigger_05_out2_set(0);
    this->trigger_05_out1_set(1);
}

void select_06_match1_bang() {
    this->trigger_05_input_bang_bang();
}

void select_06_nomatch_number_set(number ) {}

void select_06_input_number_set(number v) {
    if (v == this->select_06_test1)
        this->select_06_match1_bang();
    else
        this->select_06_nomatch_number_set(v);
}

void toggle_06_output_set(number v) {
    this->param_18_value_set(v);
    this->select_06_input_number_set(v);
}

void trigger_02_out2_set(number v) {
    this->toggle_06_value_number_set(v);
    this->toggle_05_value_number_set(v);
    this->toggle_04_value_number_set(v);
}

void trigger_02_out1_set(number ) {}

void trigger_02_input_bang_bang() {
    this->trigger_02_out2_set(0);
    this->trigger_02_out1_set(1);
}

void select_03_match1_bang() {
    this->trigger_02_input_bang_bang();
}

void select_03_nomatch_number_set(number ) {}

void select_03_input_number_set(number v) {
    if (v == this->select_03_test1)
        this->select_03_match1_bang();
    else
        this->select_03_nomatch_number_set(v);
}

void toggle_03_output_set(number v) {
    this->param_11_value_set(v);
    this->select_03_input_number_set(v);
}

void toggle_03_value_bang_bang() {
    number val = (this->toggle_03_value_number == 1 ? 0 : 1);
    this->toggle_03_value_number_set(val);
}

void select_02_match2_bang() {
    this->toggle_03_value_bang_bang();
}

void toggle_04_value_bang_bang() {
    number val = (this->toggle_04_value_number == 1 ? 0 : 1);
    this->toggle_04_value_number_set(val);
}

void select_02_match3_bang() {
    this->toggle_04_value_bang_bang();
}

void toggle_05_value_bang_bang() {
    number val = (this->toggle_05_value_number == 1 ? 0 : 1);
    this->toggle_05_value_number_set(val);
}

void select_02_match4_bang() {
    this->toggle_05_value_bang_bang();
}

void toggle_06_value_bang_bang() {
    number val = (this->toggle_06_value_number == 1 ? 0 : 1);
    this->toggle_06_value_number_set(val);
}

void select_02_match5_bang() {
    this->toggle_06_value_bang_bang();
}

void select_02_nomatch_number_set(number ) {}

void select_02_input_number_set(number v) {
    if (v == this->select_02_test1)
        this->select_02_match1_bang();
    else if (v == this->select_02_test2)
        this->select_02_match2_bang();
    else if (v == this->select_02_test3)
        this->select_02_match3_bang();
    else if (v == this->select_02_test4)
        this->select_02_match4_bang();
    else if (v == this->select_02_test5)
        this->select_02_match5_bang();
    else
        this->select_02_nomatch_number_set(v);
}

void counter_01_output_set(number v) {
    this->counter_01_output = v;
    this->select_02_input_number_set(v);
}

void counter_01_overflow_bang_bang() {}

static number counter_01_overflow_number_constrain(number v) {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void counter_01_overflow_number_set(number v) {
    v = this->counter_01_overflow_number_constrain(v);
    this->counter_01_overflow_number = v;
}

void counter_01_carry_set(number v) {
    this->counter_01_carry = v;
}

void counter_01_underflow_bang_bang() {}

static number counter_01_underflow_number_constrain(number v) {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void counter_01_underflow_number_set(number v) {
    v = this->counter_01_underflow_number_constrain(v);
    this->counter_01_underflow_number = v;
}

void counter_01_input_bang() {
    this->counter_01_output_set(this->counter_01_count);
    this->counter_01_inc();

    if (this->counter_01_count > this->counter_01_maximum) {
        if (this->counter_01_direction == 2) {
            this->counter_01_phase = !(bool)(this->counter_01_phase);
            this->counter_01_count = this->counter_01_maximum;
            this->counter_01_inc();
        } else
            this->counter_01_count = this->counter_01_minimum;

        if ((bool)(!(bool)(this->counter_01_overflow_number))) {
            if (this->counter_01_carryflag == 1)
                this->counter_01_overflow_bang_bang();
            else
                this->counter_01_overflow_number_set(1);
        }

        this->counter_01_carry_set(this->counter_01_carry + 1);
    } else if ((bool)(this->counter_01_overflow_number) && this->counter_01_carryflag == 0)
        this->counter_01_overflow_number_set(0);

    if (this->counter_01_count < this->counter_01_minimum) {
        if (this->counter_01_direction == 2) {
            this->counter_01_phase = !(bool)(this->counter_01_phase);
            this->counter_01_count = this->counter_01_minimum;
            this->counter_01_inc();
        } else
            this->counter_01_count = this->counter_01_maximum;

        if ((bool)(!(bool)(this->counter_01_underflow_number))) {
            if (this->counter_01_carryflag == 1)
                this->counter_01_underflow_bang_bang();
            else
                this->counter_01_underflow_number_set(1);
        }

        this->counter_01_carry_set(this->counter_01_carry + 1);
    } else if ((bool)(this->counter_01_underflow_number) && this->counter_01_carryflag == 0)
        this->counter_01_underflow_number_set(0);
}

void trigger_01_out1_bang() {
    this->counter_01_input_bang();
}

void trigger_01_input_bang_bang() {
    this->trigger_01_out1_bang();
}

void select_01_match1_bang() {
    this->trigger_01_input_bang_bang();
}

void select_01_nomatch_number_set(number ) {}

void select_01_input_number_set(number v) {
    if (v == this->select_01_test1)
        this->select_01_match1_bang();
    else
        this->select_01_nomatch_number_set(v);
}

static number param_12_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

static number param_13_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void p_04_in2_number_set(number v) {
    this->p_04->updateTime(this->_currentTime);
    this->p_04->eventinlet_04_out1_number_set(v);
}

void expr_07_out1_set(number v) {
    this->expr_07_out1 = v;
    this->p_04_in2_number_set(this->expr_07_out1);
}

void expr_07_in1_set(number in1) {
    this->expr_07_in1 = in1;

    this->expr_07_out1_set(
        (this->expr_07_in2 == 0 ? 0 : rnbo_fround((this->expr_07_in2 == 0. ? 0. : this->expr_07_in1 * 1 / this->expr_07_in2)) * this->expr_07_in2)
    );//#map:round_obj-46:1
}

void expr_07_in2_set(number v) {
    this->expr_07_in2 = v;
}

void scale_03_out_set(const list& v) {
    this->scale_03_out = jsCreateListCopy(v);

    {
        if (v->length > 1)
            this->expr_07_in2_set(v[1]);

        number converted = (v->length > 0 ? v[0] : 0);
        this->expr_07_in1_set(converted);
    }
}

void scale_03_input_set(const list& v) {
    this->scale_03_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_03_inlow,
            this->scale_03_inhigh,
            this->scale_03_outlow,
            this->scale_03_outhigh,
            this->scale_03_power
        ));
    }

    this->scale_03_out_set(tmp);
}

void latch_02_out1_set(number v) {
    {
        list converted = {v};
        this->scale_03_input_set(converted);
    }
}

void latch_02_x_set(number x) {
    this->latch_02_x = x;
    auto control = this->latch_02_control;

    if (control != 0.)
        this->latch_02_value = x;

    {
        this->latch_02_out1_set(this->latch_02_value);
        return;
    }
}

static number param_15_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void latch_02_control_set(number v) {
    this->latch_02_control = v;
}

void expr_08_out1_set(number v) {
    this->expr_08_out1 = v;
    this->latch_02_control_set(this->expr_08_out1);
}

void expr_08_in1_set(number in1) {
    this->expr_08_in1 = in1;
    this->expr_08_out1_set(this->expr_08_in1 >= this->expr_08_in2);//#map:>=_obj-111:1
}

static number param_17_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

static number param_19_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

static number param_20_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void select_08_match1_bang() {}

static number param_21_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void param_21_value_set(number v) {
    v = this->param_21_value_constrain(v);
    this->param_21_value = v;
    this->sendParameter(19, false);

    if (this->param_21_value != this->param_21_lastValue) {
        this->getEngine()->presetTouched();
        this->param_21_lastValue = this->param_21_value;
    }
}

static number param_24_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void param_24_value_set(number v) {
    v = this->param_24_value_constrain(v);
    this->param_24_value = v;
    this->sendParameter(22, false);

    if (this->param_24_value != this->param_24_lastValue) {
        this->getEngine()->presetTouched();
        this->param_24_lastValue = this->param_24_value;
    }
}

static number param_23_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void param_23_value_set(number v) {
    v = this->param_23_value_constrain(v);
    this->param_23_value = v;
    this->sendParameter(21, false);

    if (this->param_23_value != this->param_23_lastValue) {
        this->getEngine()->presetTouched();
        this->param_23_lastValue = this->param_23_value;
    }
}

void toggle_10_value_number_set(number v) {
    if (this->stackprotect_check())
        return;

    this->toggle_10_value_number_setter(v);
    v = this->toggle_10_value_number;
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("toggle_obj-14"), v, this->_currentTime);
    this->toggle_10_output_set(v);
}

static number param_22_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void param_22_value_set(number v) {
    v = this->param_22_value_constrain(v);
    this->param_22_value = v;
    this->sendParameter(20, false);

    if (this->param_22_value != this->param_22_lastValue) {
        this->getEngine()->presetTouched();
        this->param_22_lastValue = this->param_22_value;
    }
}

void toggle_09_value_number_set(number v) {
    if (this->stackprotect_check())
        return;

    this->toggle_09_value_number_setter(v);
    v = this->toggle_09_value_number;
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("toggle_obj-15"), v, this->_currentTime);
    this->toggle_09_output_set(v);
}

void toggle_07_value_number_set(number v) {
    if (this->stackprotect_check())
        return;

    this->toggle_07_value_number_setter(v);
    v = this->toggle_07_value_number;
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("toggle_obj-17"), v, this->_currentTime);
    this->toggle_07_output_set(v);
}

void trigger_08_out2_set(number v) {
    this->toggle_10_value_number_set(v);
    this->toggle_09_value_number_set(v);
    this->toggle_07_value_number_set(v);
}

void trigger_08_out1_set(number ) {}

void trigger_08_input_bang_bang() {
    this->trigger_08_out2_set(0);
    this->trigger_08_out1_set(1);
}

void select_10_match1_bang() {
    this->trigger_08_input_bang_bang();
}

void select_10_nomatch_number_set(number ) {}

void select_10_input_number_set(number v) {
    if (v == this->select_10_test1)
        this->select_10_match1_bang();
    else
        this->select_10_nomatch_number_set(v);
}

void toggle_08_output_set(number v) {
    this->param_22_value_set(v);
    this->select_10_input_number_set(v);
}

void toggle_08_value_number_set(number v) {
    this->toggle_08_value_number_setter(v);
    v = this->toggle_08_value_number;
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("toggle_obj-16"), v, this->_currentTime);
    this->toggle_08_output_set(v);
}

void trigger_09_out2_set(number v) {
    this->toggle_10_value_number_set(v);
    this->toggle_08_value_number_set(v);
    this->toggle_07_value_number_set(v);
}

void trigger_09_out1_set(number ) {}

void trigger_09_input_bang_bang() {
    this->trigger_09_out2_set(0);
    this->trigger_09_out1_set(1);
}

void select_11_match1_bang() {
    this->trigger_09_input_bang_bang();
}

void select_11_nomatch_number_set(number ) {}

void select_11_input_number_set(number v) {
    if (v == this->select_11_test1)
        this->select_11_match1_bang();
    else
        this->select_11_nomatch_number_set(v);
}

void toggle_09_output_set(number v) {
    this->param_23_value_set(v);
    this->select_11_input_number_set(v);
}

void trigger_10_out2_set(number v) {
    this->toggle_09_value_number_set(v);
    this->toggle_08_value_number_set(v);
    this->toggle_07_value_number_set(v);
}

void trigger_10_out1_set(number ) {}

void trigger_10_input_bang_bang() {
    this->trigger_10_out2_set(0);
    this->trigger_10_out1_set(1);
}

void select_12_match1_bang() {
    this->trigger_10_input_bang_bang();
}

void select_12_nomatch_number_set(number ) {}

void select_12_input_number_set(number v) {
    if (v == this->select_12_test1)
        this->select_12_match1_bang();
    else
        this->select_12_nomatch_number_set(v);
}

void toggle_10_output_set(number v) {
    this->param_24_value_set(v);
    this->select_12_input_number_set(v);
}

void trigger_07_out2_set(number v) {
    this->toggle_10_value_number_set(v);
    this->toggle_09_value_number_set(v);
    this->toggle_08_value_number_set(v);
}

void trigger_07_out1_set(number ) {}

void trigger_07_input_bang_bang() {
    this->trigger_07_out2_set(0);
    this->trigger_07_out1_set(1);
}

void select_09_match1_bang() {
    this->trigger_07_input_bang_bang();
}

void select_09_nomatch_number_set(number ) {}

void select_09_input_number_set(number v) {
    if (v == this->select_09_test1)
        this->select_09_match1_bang();
    else
        this->select_09_nomatch_number_set(v);
}

void toggle_07_output_set(number v) {
    this->param_21_value_set(v);
    this->select_09_input_number_set(v);
}

void toggle_07_value_bang_bang() {
    number val = (this->toggle_07_value_number == 1 ? 0 : 1);
    this->toggle_07_value_number_set(val);
}

void select_08_match2_bang() {
    this->toggle_07_value_bang_bang();
}

void toggle_08_value_bang_bang() {
    number val = (this->toggle_08_value_number == 1 ? 0 : 1);
    this->toggle_08_value_number_set(val);
}

void select_08_match3_bang() {
    this->toggle_08_value_bang_bang();
}

void toggle_09_value_bang_bang() {
    number val = (this->toggle_09_value_number == 1 ? 0 : 1);
    this->toggle_09_value_number_set(val);
}

void select_08_match4_bang() {
    this->toggle_09_value_bang_bang();
}

void toggle_10_value_bang_bang() {
    number val = (this->toggle_10_value_number == 1 ? 0 : 1);
    this->toggle_10_value_number_set(val);
}

void select_08_match5_bang() {
    this->toggle_10_value_bang_bang();
}

void select_08_nomatch_number_set(number ) {}

void select_08_input_number_set(number v) {
    if (v == this->select_08_test1)
        this->select_08_match1_bang();
    else if (v == this->select_08_test2)
        this->select_08_match2_bang();
    else if (v == this->select_08_test3)
        this->select_08_match3_bang();
    else if (v == this->select_08_test4)
        this->select_08_match4_bang();
    else if (v == this->select_08_test5)
        this->select_08_match5_bang();
    else
        this->select_08_nomatch_number_set(v);
}

void counter_02_output_set(number v) {
    this->counter_02_output = v;
    this->select_08_input_number_set(v);
}

void counter_02_overflow_bang_bang() {}

static number counter_02_overflow_number_constrain(number v) {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void counter_02_overflow_number_set(number v) {
    v = this->counter_02_overflow_number_constrain(v);
    this->counter_02_overflow_number = v;
}

void counter_02_carry_set(number v) {
    this->counter_02_carry = v;
}

void counter_02_underflow_bang_bang() {}

static number counter_02_underflow_number_constrain(number v) {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void counter_02_underflow_number_set(number v) {
    v = this->counter_02_underflow_number_constrain(v);
    this->counter_02_underflow_number = v;
}

void counter_02_input_bang() {
    this->counter_02_output_set(this->counter_02_count);
    this->counter_02_inc();

    if (this->counter_02_count > this->counter_02_maximum) {
        if (this->counter_02_direction == 2) {
            this->counter_02_phase = !(bool)(this->counter_02_phase);
            this->counter_02_count = this->counter_02_maximum;
            this->counter_02_inc();
        } else
            this->counter_02_count = this->counter_02_minimum;

        if ((bool)(!(bool)(this->counter_02_overflow_number))) {
            if (this->counter_02_carryflag == 1)
                this->counter_02_overflow_bang_bang();
            else
                this->counter_02_overflow_number_set(1);
        }

        this->counter_02_carry_set(this->counter_02_carry + 1);
    } else if ((bool)(this->counter_02_overflow_number) && this->counter_02_carryflag == 0)
        this->counter_02_overflow_number_set(0);

    if (this->counter_02_count < this->counter_02_minimum) {
        if (this->counter_02_direction == 2) {
            this->counter_02_phase = !(bool)(this->counter_02_phase);
            this->counter_02_count = this->counter_02_minimum;
            this->counter_02_inc();
        } else
            this->counter_02_count = this->counter_02_maximum;

        if ((bool)(!(bool)(this->counter_02_underflow_number))) {
            if (this->counter_02_carryflag == 1)
                this->counter_02_underflow_bang_bang();
            else
                this->counter_02_underflow_number_set(1);
        }

        this->counter_02_carry_set(this->counter_02_carry + 1);
    } else if ((bool)(this->counter_02_underflow_number) && this->counter_02_carryflag == 0)
        this->counter_02_underflow_number_set(0);
}

void trigger_06_out1_bang() {
    this->counter_02_input_bang();
}

void trigger_06_input_bang_bang() {
    this->trigger_06_out1_bang();
}

void select_07_match1_bang() {
    this->trigger_06_input_bang_bang();
}

void select_07_nomatch_number_set(number ) {}

void select_07_input_number_set(number v) {
    if (v == this->select_07_test1)
        this->select_07_match1_bang();
    else
        this->select_07_nomatch_number_set(v);
}

void transport_01_input_number_set(number v) {
    this->transport_01_input_number = v;
    this->getTopLevelPatcher()->globaltransport_setState(this->currenttime(), (v == 0 ? 0 : 1), true);
}

void toggle_01_output_set(number v) {
    this->transport_01_input_number_set(v);
}

void toggle_01_value_number_set(number v) {
    this->toggle_01_value_number_setter(v);
    v = this->toggle_01_value_number;
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("toggle_obj-37"), v, this->_currentTime);
    this->toggle_01_output_set(v);
}

void toggle_01_value_bang_bang() {
    number val = (this->toggle_01_value_number == 1 ? 0 : 1);
    this->toggle_01_value_number_set(val);
}

void loadbang_03_output_bang() {
    this->toggle_01_value_bang_bang();
}

void outport_01_input_list_set(const list& v) {
    this->getEngine()->sendListMessage(TAG("master_clock"), TAG(""), v, this->_currentTime);
}

void message_11_out_set(const list& v) {
    this->outport_01_input_list_set(v);
}

void message_11_trigger_bang() {
    this->message_11_out_set(this->message_11_set);
}

void toggle_02_output_set(number v) {
    this->message_11_trigger_bang();
    this->param_03_value_set(v);
}

void toggle_02_value_number_set(number v) {
    this->toggle_02_value_number_setter(v);
    v = this->toggle_02_value_number;
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("toggle_obj-42"), v, this->_currentTime);
    this->toggle_02_output_set(v);
}

void toggle_02_value_bang_bang() {
    number val = (this->toggle_02_value_number == 1 ? 0 : 1);
    this->toggle_02_value_number_set(val);
}

void button_03_output_bang() {
    this->toggle_02_value_bang_bang();
}

void button_03_bangval_bang() {
    this->getEngine()->sendBangMessage(TAG("bangout"), TAG("button_obj-54"), this->_currentTime);;
    this->button_03_output_bang();
}

void metro_01_tickout_bang() {
    this->button_03_bangval_bang();
}

void message_11_set_set(const list& v) {
    this->message_11_set = jsCreateListCopy(v);
    this->getEngine()->sendListMessage(TAG("listout"), TAG("message_obj-427"), v, this->_currentTime);
}

void metro_01_on_set(number v) {
    this->metro_01_on = v;
    this->getEngine()->flushClockEvents(this, 1935387534, false);;

    if ((bool)(v)) {
        {
            this->getEngine()->scheduleClockEvent(this, 1935387534, 0 + this->_currentTime);;
        }
    }
}

void phasor_01_freq_set(number v) {
    this->phasor_01_freq = v;
}

void timevalue_01_out_set(number v) {
    this->phasor_01_freq_set(v);
}

void metro_01_interval_set(number v) {
    this->metro_01_interval_setter(v);
    v = this->metro_01_interval;
}

void timevalue_02_out_set(number v) {
    this->metro_01_interval_set(v);
}

void transport_01_outtempo_set(number ) {}

void transport_01_state_set(number ) {}

void transport_01_outtimesig_set(const list& ) {}

void phasor_01_perform(number freq, SampleValue * out, Index n) {
    auto __phasor_01_lastLockedPhase = this->phasor_01_lastLockedPhase;
    auto quantum = this->hztobeats(freq);
    auto tempo = this->tempo();

    if (quantum > 0 && tempo > 0) {
        auto samplerate = this->samplerate();
        auto beattime = this->beattimeatsample(0);
        number offset = fmod(beattime, quantum);
        number nextJump = quantum - offset;
        number nextJumpInSamples = rnbo_fround(nextJump * 60 * samplerate / tempo * 1 / (number)1) * 1;
        number inc = tempo / (number)60 / samplerate;
        number oneoverquantum = (number)1 / quantum;

        for (Index i = 0; i < n; i++) {
            if ((bool)(this->transportatsample(i))) {
                out[(Index)i] = __phasor_01_lastLockedPhase = offset * oneoverquantum;
                offset += inc;
                nextJumpInSamples--;

                if (nextJumpInSamples <= 0) {
                    offset -= quantum;
                    nextJumpInSamples = rnbo_fround(quantum * 60 * samplerate / tempo * 1 / (number)1) * 1;
                }
            } else {
                out[(Index)i] = __phasor_01_lastLockedPhase;
            }
        }
    } else {
        for (Index i = 0; i < n; i++) {
            out[(Index)i] = 0;
        }
    }

    this->phasor_01_lastLockedPhase = __phasor_01_lastLockedPhase;
}

void signalsend_01_perform(const SampleValue * input, SampleValue * send, Index n) {
    for (Index i = 0; i < n; i++) {
        send[(Index)i] = input[(Index)i];
    }
}

void signalreceive_01_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void p_04_perform(
    const SampleValue * in1,
    SampleValue * out7,
    SampleValue * out8,
    SampleValue * out9,
    SampleValue * out10,
    Index n
) {
    // subpatcher: rotating_clock_divider
    ConstSampleArray<1> ins = {in1};

    SampleArray<4> outs = {out7, out8, out9, out10};
    this->p_04->process(ins, 1, outs, 4, n);
}

void p_02_perform(
    const SampleValue * in1,
    SampleValue * out3,
    SampleValue * out4,
    SampleValue * out5,
    SampleValue * out6,
    Index n
) {
    // subpatcher: rotating_clock_divider
    ConstSampleArray<1> ins = {in1};

    SampleArray<4> outs = {out3, out4, out5, out6};
    this->p_02->process(ins, 1, outs, 4, n);
}

void p_03_perform(const SampleValue * in1, SampleValue * out9, Index n) {
    // subpatcher: probability_skip
    ConstSampleArray<1> ins = {in1};

    SampleArray<1> outs = {out9};
    this->p_03->process(ins, 1, outs, 1, n);
}

void intnum_tilde_01_perform(number value, SampleValue * out1, Index n) {
    RNBO_UNUSED(value);
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = trunc(0);
    }
}

void intnum_tilde_02_perform(number value, SampleValue * out1, Index n) {
    RNBO_UNUSED(value);
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = trunc(0);
    }
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void toggle_01_value_number_setter(number v) {
    this->toggle_01_value_number = (v != 0 ? 1 : 0);
}

void metro_01_interval_setter(number v) {
    this->metro_01_interval = (v > 0 ? v : 0);
}

void toggle_02_value_number_setter(number v) {
    this->toggle_02_value_number = (v != 0 ? 1 : 0);
}

void toggle_03_value_number_setter(number v) {
    this->toggle_03_value_number = (v != 0 ? 1 : 0);
}

void toggle_04_value_number_setter(number v) {
    this->toggle_04_value_number = (v != 0 ? 1 : 0);
}

void toggle_05_value_number_setter(number v) {
    this->toggle_05_value_number = (v != 0 ? 1 : 0);
}

void toggle_06_value_number_setter(number v) {
    this->toggle_06_value_number = (v != 0 ? 1 : 0);
}

void toggle_07_value_number_setter(number v) {
    this->toggle_07_value_number = (v != 0 ? 1 : 0);
}

void toggle_08_value_number_setter(number v) {
    this->toggle_08_value_number = (v != 0 ? 1 : 0);
}

void toggle_09_value_number_setter(number v) {
    this->toggle_09_value_number = (v != 0 ? 1 : 0);
}

void toggle_10_value_number_setter(number v) {
    this->toggle_10_value_number = (v != 0 ? 1 : 0);
}

void toggle_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->toggle_01_value_number;
}

void toggle_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->toggle_01_value_number_set(preset["value"]);
}

void transport_01_onTempoChanged(number state) {
    this->transport_01_outtempo_set(state);
}

void transport_01_onTransportChanged(number state) {
    this->transport_01_state_set(state);
}

void transport_01_onTimeSignatureChanged(number numerator, number denominator) {
    this->transport_01_outtimesig_set({numerator, denominator});
}

void phasor_01_dspsetup(bool force) {
    if ((bool)(this->phasor_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->phasor_01_conv = (number)1 / this->samplerate();
    this->phasor_01_setupDone = true;
}

void param_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_02_value;
}

void param_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_02_value_set(preset["value"]);
}

void metro_01_onTransportChanged(number ) {}

void metro_01_onBeatTimeChanged(number ) {}

void param_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_03_value;
}

void param_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_03_value_set(preset["value"]);
}

void param_04_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_04_value;
}

void param_04_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_04_value_set(preset["value"]);
}

void param_05_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_05_value;
}

void param_05_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_05_value_set(preset["value"]);
}

void param_06_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_06_value;
}

void param_06_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_06_value_set(preset["value"]);
}

void toggle_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->toggle_02_value_number;
}

void toggle_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->toggle_02_value_number_set(preset["value"]);
}

void message_11_init() {
    this->message_11_set_set({1});
}

void param_07_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_07_value;
}

void param_07_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_07_value_set(preset["value"]);
}

void param_08_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_08_value;
}

void param_08_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_08_value_set(preset["value"]);
}

void param_09_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_09_value;
}

void param_09_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_09_value_set(preset["value"]);
}

void param_10_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_10_value;
}

void param_10_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_10_value_set(preset["value"]);
}

void counter_01_inc() {
    this->counter_01_count = ((bool)(this->counter_01_phase) ? this->counter_01_count + 1 : this->counter_01_count - 1);
}

void param_11_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_11_value;
}

void param_11_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_11_value_set(preset["value"]);
}

void toggle_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->toggle_03_value_number;
}

void toggle_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->toggle_03_value_number_set(preset["value"]);
}

void param_12_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_12_value;
}

void param_12_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_12_value_set(preset["value"]);
}

void param_13_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_13_value;
}

void param_13_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_13_value_set(preset["value"]);
}

void param_14_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_14_value;
}

void param_14_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_14_value_set(preset["value"]);
}

void toggle_04_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->toggle_04_value_number;
}

void toggle_04_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->toggle_04_value_number_set(preset["value"]);
}

void param_15_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_15_value;
}

void param_15_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_15_value_set(preset["value"]);
}

void param_16_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_16_value;
}

void param_16_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_16_value_set(preset["value"]);
}

void toggle_05_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->toggle_05_value_number;
}

void toggle_05_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->toggle_05_value_number_set(preset["value"]);
}

void param_17_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_17_value;
}

void param_17_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_17_value_set(preset["value"]);
}

void param_18_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_18_value;
}

void param_18_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_18_value_set(preset["value"]);
}

void toggle_06_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->toggle_06_value_number;
}

void toggle_06_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->toggle_06_value_number_set(preset["value"]);
}

void param_19_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_19_value;
}

void param_19_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_19_value_set(preset["value"]);
}

void param_20_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_20_value;
}

void param_20_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_20_value_set(preset["value"]);
}

void counter_02_inc() {
    this->counter_02_count = ((bool)(this->counter_02_phase) ? this->counter_02_count + 1 : this->counter_02_count - 1);
}

void param_21_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_21_value;
}

void param_21_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_21_value_set(preset["value"]);
}

void toggle_07_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->toggle_07_value_number;
}

void toggle_07_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->toggle_07_value_number_set(preset["value"]);
}

void param_22_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_22_value;
}

void param_22_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_22_value_set(preset["value"]);
}

void toggle_08_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->toggle_08_value_number;
}

void toggle_08_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->toggle_08_value_number_set(preset["value"]);
}

void param_23_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_23_value;
}

void param_23_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_23_value_set(preset["value"]);
}

void toggle_09_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->toggle_09_value_number;
}

void toggle_09_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->toggle_09_value_number_set(preset["value"]);
}

void param_24_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_24_value;
}

void param_24_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_24_value_set(preset["value"]);
}

void toggle_10_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->toggle_10_value_number;
}

void toggle_10_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->toggle_10_value_number_set(preset["value"]);
}

void timevalue_01_sendValue() {
    {
        {
            {
                {
                    {
                        {
                            this->timevalue_01_out_set(this->tickstohz(120));
                        }
                    }
                }
            }
        }
    }
}

void timevalue_01_onTempoChanged(number tempo) {
    RNBO_UNUSED(tempo);

    {
        this->timevalue_01_sendValue();
    }
}

void timevalue_01_onSampleRateChanged(number ) {}

void timevalue_01_onTimeSignatureChanged(number , number ) {}

void timevalue_02_sendValue() {
    {
        {
            {
                {
                    this->timevalue_02_out_set(this->tickstoms(240));
                }
            }
        }
    }
}

void timevalue_02_onTempoChanged(number tempo) {
    RNBO_UNUSED(tempo);

    {
        this->timevalue_02_sendValue();
    }
}

void timevalue_02_onSampleRateChanged(number ) {}

void timevalue_02_onTimeSignatureChanged(number , number ) {}

Index globaltransport_getSampleOffset(MillisecondTime time) {
    return this->mstosamps(this->maximum(0, time - this->getEngine()->getCurrentTime()));
}

number globaltransport_getTempoAtSample(SampleIndex sampleOffset) {
    return (sampleOffset >= 0 && sampleOffset < this->vs ? this->globaltransport_tempo[(Index)sampleOffset] : this->globaltransport_lastTempo);
}

number globaltransport_getStateAtSample(SampleIndex sampleOffset) {
    return (sampleOffset >= 0 && sampleOffset < this->vs ? this->globaltransport_state[(Index)sampleOffset] : this->globaltransport_lastState);
}

number globaltransport_getState(MillisecondTime time) {
    return this->globaltransport_getStateAtSample(this->globaltransport_getSampleOffset(time));
}

number globaltransport_getBeatTime(MillisecondTime time) {
    number i = 2;

    while (i < this->globaltransport_beatTimeChanges->length && this->globaltransport_beatTimeChanges[(Index)(i + 1)] <= time) {
        i += 2;
    }

    i -= 2;
    number beatTimeBase = this->globaltransport_beatTimeChanges[(Index)i];

    if (this->globaltransport_getState(time) == 0)
        return beatTimeBase;

    number beatTimeBaseMsTime = this->globaltransport_beatTimeChanges[(Index)(i + 1)];
    number diff = time - beatTimeBaseMsTime;
    return beatTimeBase + this->mstobeats(diff);
}

bool globaltransport_setTempo(MillisecondTime time, number tempo, bool notify) {
    if ((bool)(notify)) {
        this->processTempoEvent(time, tempo);
        this->globaltransport_notify = true;
    } else {
        Index offset = (Index)(this->globaltransport_getSampleOffset(time));

        if (this->globaltransport_getTempoAtSample(offset) != tempo) {
            this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime(time));
            this->globaltransport_beatTimeChanges->push(time);
            fillSignal(this->globaltransport_tempo, this->vs, tempo, offset);
            this->globaltransport_lastTempo = tempo;
            this->globaltransport_tempoNeedsReset = true;
            return true;
        }
    }

    return false;
}

number globaltransport_getTempo(MillisecondTime time) {
    return this->globaltransport_getTempoAtSample(this->globaltransport_getSampleOffset(time));
}

bool globaltransport_setState(MillisecondTime time, number state, bool notify) {
    if ((bool)(notify)) {
        this->processTransportEvent(time, TransportState(state));
        this->globaltransport_notify = true;
    } else {
        Index offset = (Index)(this->globaltransport_getSampleOffset(time));

        if (this->globaltransport_getStateAtSample(offset) != state) {
            fillSignal(this->globaltransport_state, this->vs, state, offset);
            this->globaltransport_lastState = TransportState(state);
            this->globaltransport_stateNeedsReset = true;

            if (state == 0) {
                this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime(time));
                this->globaltransport_beatTimeChanges->push(time);
            }

            return true;
        }
    }

    return false;
}

bool globaltransport_setBeatTime(MillisecondTime time, number beattime, bool notify) {
    if ((bool)(notify)) {
        this->processBeatTimeEvent(time, beattime);
        this->globaltransport_notify = true;
        return false;
    } else {
        bool beatTimeHasChanged = false;
        float oldBeatTime = (float)(this->globaltransport_getBeatTime(time));
        float newBeatTime = (float)(beattime);

        if (oldBeatTime != newBeatTime) {
            beatTimeHasChanged = true;
        }

        this->globaltransport_beatTimeChanges->push(beattime);
        this->globaltransport_beatTimeChanges->push(time);
        return beatTimeHasChanged;
    }
}

number globaltransport_getBeatTimeAtSample(SampleIndex sampleOffset) {
    auto msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getBeatTime(this->getEngine()->getCurrentTime() + msOffset);
}

array<number, 2> globaltransport_getTimeSignature(MillisecondTime time) {
    number i = 3;

    while (i < this->globaltransport_timeSignatureChanges->length && this->globaltransport_timeSignatureChanges[(Index)(i + 2)] <= time) {
        i += 3;
    }

    i -= 3;

    return {
        this->globaltransport_timeSignatureChanges[(Index)i],
        this->globaltransport_timeSignatureChanges[(Index)(i + 1)]
    };
}

array<number, 2> globaltransport_getTimeSignatureAtSample(SampleIndex sampleOffset) {
    auto msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getTimeSignature(this->getEngine()->getCurrentTime() + msOffset);
}

bool globaltransport_setTimeSignature(MillisecondTime time, number numerator, number denominator, bool notify) {
    if ((bool)(notify)) {
        this->processTimeSignatureEvent(time, (int)(numerator), (int)(denominator));
        this->globaltransport_notify = true;
    } else {
        array<number, 2> currentSig = this->globaltransport_getTimeSignature(time);

        if (currentSig[0] != numerator || currentSig[1] != denominator) {
            this->globaltransport_timeSignatureChanges->push(numerator);
            this->globaltransport_timeSignatureChanges->push(denominator);
            this->globaltransport_timeSignatureChanges->push(time);
            return true;
        }
    }

    return false;
}

void globaltransport_advance() {
    if ((bool)(this->globaltransport_tempoNeedsReset)) {
        fillSignal(this->globaltransport_tempo, this->vs, this->globaltransport_lastTempo);
        this->globaltransport_tempoNeedsReset = false;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTempoEvent(this->globaltransport_lastTempo);
        }
    }

    if ((bool)(this->globaltransport_stateNeedsReset)) {
        fillSignal(this->globaltransport_state, this->vs, this->globaltransport_lastState);
        this->globaltransport_stateNeedsReset = false;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTransportEvent(TransportState(this->globaltransport_lastState));
        }
    }

    if (this->globaltransport_beatTimeChanges->length > 2) {
        this->globaltransport_beatTimeChanges[0] = this->globaltransport_beatTimeChanges[(Index)(this->globaltransport_beatTimeChanges->length - 2)];
        this->globaltransport_beatTimeChanges[1] = this->globaltransport_beatTimeChanges[(Index)(this->globaltransport_beatTimeChanges->length - 1)];
        this->globaltransport_beatTimeChanges->length = 2;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendBeatTimeEvent(this->globaltransport_beatTimeChanges[0]);
        }
    }

    if (this->globaltransport_timeSignatureChanges->length > 3) {
        this->globaltransport_timeSignatureChanges[0] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 3)];
        this->globaltransport_timeSignatureChanges[1] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 2)];
        this->globaltransport_timeSignatureChanges[2] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 1)];
        this->globaltransport_timeSignatureChanges->length = 3;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTimeSignatureEvent(
                (int)(this->globaltransport_timeSignatureChanges[0]),
                (int)(this->globaltransport_timeSignatureChanges[1])
            );
        }
    }

    this->globaltransport_notify = false;
}

void globaltransport_dspsetup(bool force) {
    if ((bool)(this->globaltransport_setupDone) && (bool)(!(bool)(force)))
        return;

    fillSignal(this->globaltransport_tempo, this->vs, this->globaltransport_lastTempo);
    this->globaltransport_tempoNeedsReset = false;
    fillSignal(this->globaltransport_state, this->vs, this->globaltransport_lastState);
    this->globaltransport_stateNeedsReset = false;
    this->globaltransport_setupDone = true;
}

bool stackprotect_check() {
    this->stackprotect_count++;

    if (this->stackprotect_count > 128) {
        console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
        return true;
    }

    return false;
}

void updateTime(MillisecondTime time) {
    this->_currentTime = time;
    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));

    if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;

    if (this->sampleOffsetIntoNextAudioBuffer < 0)
        this->sampleOffsetIntoNextAudioBuffer = 0;
}

void assign_defaults()
{
    p_02_target = 0;
    toggle_01_value_number = 0;
    toggle_01_value_number_setter(toggle_01_value_number);
    transport_01_input_number = 0;
    transport_01_position = 0;
    transport_01_tempo = 120;
    transport_01_ticks = 0;
    phasor_01_freq = 0;
    scale_01_inlow = 0;
    scale_01_inhigh = 1;
    scale_01_outlow = 60;
    scale_01_outhigh = 160;
    scale_01_power = 1;
    p_03_target = 0;
    param_02_value = 0;
    metro_01_on = 1;
    metro_01_interval = 0;
    metro_01_interval_setter(metro_01_interval);
    param_03_value = 0;
    expr_05_in1 = 0;
    expr_05_in2 = 1;
    expr_05_out1 = 0;
    scale_02_inlow = 0;
    scale_02_inhigh = 1;
    scale_02_outlow = 0;
    scale_02_outhigh = 8;
    scale_02_power = 1;
    latch_01_x = 0;
    latch_01_control = 0;
    param_04_value = 0;
    expr_06_in1 = 0;
    expr_06_in2 = 0.3;
    expr_06_out1 = 0;
    param_05_value = 0;
    param_06_value = 0;
    toggle_02_value_number = 0;
    toggle_02_value_number_setter(toggle_02_value_number);
    param_07_value = 0;
    p_04_target = 0;
    param_08_value = 0;
    param_09_value = 0;
    select_01_test1 = 1;
    param_10_value = 0;
    counter_01_carryflag = 0;
    counter_01_direction = 0;
    counter_01_resetnext_number = 0;
    counter_01_resetnow_number = 0;
    counter_01_maximum = 4;
    counter_01_output = 0;
    counter_01_underflow_number = 0;
    counter_01_overflow_number = 0;
    counter_01_carry = 0;
    counter_01_minimum = 1;
    select_02_test1 = 0;
    select_02_test2 = 1;
    select_02_test3 = 2;
    select_02_test4 = 3;
    select_02_test5 = 4;
    param_11_value = 0;
    toggle_03_value_number = 0;
    toggle_03_value_number_setter(toggle_03_value_number);
    select_03_test1 = 1;
    param_12_value = 0;
    latch_02_x = 0;
    latch_02_control = 0;
    expr_07_in1 = 0;
    expr_07_in2 = 1;
    expr_07_out1 = 0;
    scale_03_inlow = 0;
    scale_03_inhigh = 1;
    scale_03_outlow = 0;
    scale_03_outhigh = 8;
    scale_03_power = 1;
    param_13_value = 0;
    param_14_value = 0;
    toggle_04_value_number = 0;
    toggle_04_value_number_setter(toggle_04_value_number);
    select_04_test1 = 1;
    expr_08_in1 = 0;
    expr_08_in2 = 0.3;
    expr_08_out1 = 0;
    param_15_value = 0;
    param_16_value = 0;
    toggle_05_value_number = 0;
    toggle_05_value_number_setter(toggle_05_value_number);
    select_05_test1 = 1;
    param_17_value = 0;
    param_18_value = 0;
    toggle_06_value_number = 0;
    toggle_06_value_number_setter(toggle_06_value_number);
    select_06_test1 = 1;
    param_19_value = 0;
    select_07_test1 = 1;
    param_20_value = 0;
    counter_02_carryflag = 0;
    counter_02_direction = 0;
    counter_02_resetnext_number = 0;
    counter_02_resetnow_number = 0;
    counter_02_maximum = 4;
    counter_02_output = 0;
    counter_02_underflow_number = 0;
    counter_02_overflow_number = 0;
    counter_02_carry = 0;
    counter_02_minimum = 1;
    select_08_test1 = 0;
    select_08_test2 = 1;
    select_08_test3 = 2;
    select_08_test4 = 3;
    select_08_test5 = 4;
    param_21_value = 0;
    toggle_07_value_number = 0;
    toggle_07_value_number_setter(toggle_07_value_number);
    select_09_test1 = 1;
    param_22_value = 0;
    toggle_08_value_number = 0;
    toggle_08_value_number_setter(toggle_08_value_number);
    select_10_test1 = 1;
    param_23_value = 0;
    toggle_09_value_number = 0;
    toggle_09_value_number_setter(toggle_09_value_number);
    select_11_test1 = 1;
    param_24_value = 0;
    toggle_10_value_number = 0;
    toggle_10_value_number_setter(toggle_10_value_number);
    select_12_test1 = 1;
    intnum_tilde_01_value = 0;
    intnum_tilde_02_value = 0;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    signals[0] = nullptr;
    signals[1] = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.00002267573696;
    toggle_01_lastValue = 0;
    phasor_01_sigbuf = nullptr;
    phasor_01_lastLockedPhase = 0;
    phasor_01_conv = 0;
    phasor_01_setupDone = false;
    param_02_lastValue = 0;
    metro_01_last = -1;
    metro_01_next = -1;
    param_03_lastValue = 0;
    latch_01_value = 0;
    param_04_lastValue = 0;
    param_05_lastValue = 0;
    param_06_lastValue = 0;
    toggle_02_lastValue = 0;
    param_07_lastValue = 0;
    param_08_lastValue = 0;
    param_09_lastValue = 0;
    param_10_lastValue = 0;
    counter_01_count = 1;
    counter_01_phase = true;
    param_11_lastValue = 0;
    toggle_03_lastValue = 0;
    param_12_lastValue = 0;
    latch_02_value = 0;
    param_13_lastValue = 0;
    param_14_lastValue = 0;
    toggle_04_lastValue = 0;
    param_15_lastValue = 0;
    param_16_lastValue = 0;
    toggle_05_lastValue = 0;
    param_17_lastValue = 0;
    param_18_lastValue = 0;
    toggle_06_lastValue = 0;
    param_19_lastValue = 0;
    param_20_lastValue = 0;
    counter_02_count = 1;
    counter_02_phase = true;
    param_21_lastValue = 0;
    toggle_07_lastValue = 0;
    param_22_lastValue = 0;
    toggle_08_lastValue = 0;
    param_23_lastValue = 0;
    toggle_09_lastValue = 0;
    param_24_lastValue = 0;
    toggle_10_lastValue = 0;
    globaltransport_tempo = nullptr;
    globaltransport_tempoNeedsReset = false;
    globaltransport_lastTempo = 120;
    globaltransport_state = nullptr;
    globaltransport_stateNeedsReset = false;
    globaltransport_lastState = 0;
    globaltransport_beatTimeChanges = { 0, 0 };
    globaltransport_timeSignatureChanges = { 4, 4, 0 };
    globaltransport_notify = false;
    globaltransport_setupDone = false;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

// member variables

    number p_02_target;
    number toggle_01_value_number;
    number transport_01_input_number;
    number transport_01_position;
    number transport_01_tempo;
    list transport_01_timesig;
    number transport_01_ticks;
    number phasor_01_freq;
    list scale_01_input;
    number scale_01_inlow;
    number scale_01_inhigh;
    number scale_01_outlow;
    number scale_01_outhigh;
    number scale_01_power;
    list scale_01_out;
    number p_03_target;
    number param_02_value;
    number metro_01_on;
    number metro_01_interval;
    number param_03_value;
    number expr_05_in1;
    number expr_05_in2;
    number expr_05_out1;
    list scale_02_input;
    number scale_02_inlow;
    number scale_02_inhigh;
    number scale_02_outlow;
    number scale_02_outhigh;
    number scale_02_power;
    list scale_02_out;
    number latch_01_x;
    number latch_01_control;
    number param_04_value;
    number expr_06_in1;
    number expr_06_in2;
    number expr_06_out1;
    number param_05_value;
    number param_06_value;
    number toggle_02_value_number;
    list message_11_set;
    number param_07_value;
    number p_04_target;
    number param_08_value;
    number param_09_value;
    number select_01_test1;
    number param_10_value;
    Int counter_01_carryflag;
    number counter_01_direction;
    number counter_01_resetnext_number;
    number counter_01_resetnow_number;
    number counter_01_maximum;
    number counter_01_output;
    number counter_01_underflow_number;
    number counter_01_overflow_number;
    number counter_01_carry;
    number counter_01_minimum;
    number select_02_test1;
    number select_02_test2;
    number select_02_test3;
    number select_02_test4;
    number select_02_test5;
    number param_11_value;
    number toggle_03_value_number;
    number select_03_test1;
    number param_12_value;
    number latch_02_x;
    number latch_02_control;
    number expr_07_in1;
    number expr_07_in2;
    number expr_07_out1;
    list scale_03_input;
    number scale_03_inlow;
    number scale_03_inhigh;
    number scale_03_outlow;
    number scale_03_outhigh;
    number scale_03_power;
    list scale_03_out;
    number param_13_value;
    number param_14_value;
    number toggle_04_value_number;
    number select_04_test1;
    number expr_08_in1;
    number expr_08_in2;
    number expr_08_out1;
    number param_15_value;
    number param_16_value;
    number toggle_05_value_number;
    number select_05_test1;
    number param_17_value;
    number param_18_value;
    number toggle_06_value_number;
    number select_06_test1;
    number param_19_value;
    number select_07_test1;
    number param_20_value;
    Int counter_02_carryflag;
    number counter_02_direction;
    number counter_02_resetnext_number;
    number counter_02_resetnow_number;
    number counter_02_maximum;
    number counter_02_output;
    number counter_02_underflow_number;
    number counter_02_overflow_number;
    number counter_02_carry;
    number counter_02_minimum;
    number select_08_test1;
    number select_08_test2;
    number select_08_test3;
    number select_08_test4;
    number select_08_test5;
    number param_21_value;
    number toggle_07_value_number;
    number select_09_test1;
    number param_22_value;
    number toggle_08_value_number;
    number select_10_test1;
    number param_23_value;
    number toggle_09_value_number;
    number select_11_test1;
    number param_24_value;
    number toggle_10_value_number;
    number select_12_test1;
    number intnum_tilde_01_value;
    number intnum_tilde_02_value;
    MillisecondTime _currentTime;
    SampleIndex audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[2];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    number toggle_01_lastValue;
    signal phasor_01_sigbuf;
    number phasor_01_lastLockedPhase;
    number phasor_01_conv;
    bool phasor_01_setupDone;
    number param_02_lastValue;
    number metro_01_last;
    number metro_01_next;
    number param_03_lastValue;
    number latch_01_value;
    number param_04_lastValue;
    number param_05_lastValue;
    number param_06_lastValue;
    number toggle_02_lastValue;
    number param_07_lastValue;
    number param_08_lastValue;
    number param_09_lastValue;
    number param_10_lastValue;
    number counter_01_count;
    bool counter_01_phase;
    number param_11_lastValue;
    number toggle_03_lastValue;
    number param_12_lastValue;
    number latch_02_value;
    number param_13_lastValue;
    number param_14_lastValue;
    number toggle_04_lastValue;
    number param_15_lastValue;
    number param_16_lastValue;
    number toggle_05_lastValue;
    number param_17_lastValue;
    number param_18_lastValue;
    number toggle_06_lastValue;
    number param_19_lastValue;
    number param_20_lastValue;
    number counter_02_count;
    bool counter_02_phase;
    number param_21_lastValue;
    number toggle_07_lastValue;
    number param_22_lastValue;
    number toggle_08_lastValue;
    number param_23_lastValue;
    number toggle_09_lastValue;
    number param_24_lastValue;
    number toggle_10_lastValue;
    signal globaltransport_tempo;
    bool globaltransport_tempoNeedsReset;
    number globaltransport_lastTempo;
    signal globaltransport_state;
    bool globaltransport_stateNeedsReset;
    number globaltransport_lastState;
    list globaltransport_beatTimeChanges;
    list globaltransport_timeSignatureChanges;
    bool globaltransport_notify;
    bool globaltransport_setupDone;
    number stackprotect_count;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;
    RNBOSubpatcher_3775* p_02;
    RNBOSubpatcher_3776* p_03;
    RNBOSubpatcher_3777* p_04;

};

PatcherInterface* creaternbomatic()
{
    return new rnbomatic();
}

#ifndef RNBO_NO_PATCHERFACTORY

extern "C" PatcherFactoryFunctionPtr GetPatcherFactoryFunction(PlatformInterface* platformInterface)
#else

extern "C" PatcherFactoryFunctionPtr rnbomaticFactoryFunction(PlatformInterface* platformInterface)
#endif

{
    Platform::set(platformInterface);
    return creaternbomatic;
}

} // end RNBO namespace

