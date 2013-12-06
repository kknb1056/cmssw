// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: l1menu.proto

#ifndef PROTOBUF_l1menu_2eproto__INCLUDED
#define PROTOBUF_l1menu_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace l1menuprotobuf {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_l1menu_2eproto();
void protobuf_AssignDesc_l1menu_2eproto();
void protobuf_ShutdownFile_l1menu_2eproto();

class Trigger;
class Trigger_TriggerParameter;
class Event;
class Run;
class SampleHeader;

// ===================================================================

class Trigger_TriggerParameter : public ::google::protobuf::Message {
 public:
  Trigger_TriggerParameter();
  virtual ~Trigger_TriggerParameter();
  
  Trigger_TriggerParameter(const Trigger_TriggerParameter& from);
  
  inline Trigger_TriggerParameter& operator=(const Trigger_TriggerParameter& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Trigger_TriggerParameter& default_instance();
  
  void Swap(Trigger_TriggerParameter* other);
  
  // implements Message ----------------------------------------------
  
  Trigger_TriggerParameter* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Trigger_TriggerParameter& from);
  void MergeFrom(const Trigger_TriggerParameter& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required string name = 1;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 1;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  
  // required float value = 2;
  inline bool has_value() const;
  inline void clear_value();
  static const int kValueFieldNumber = 2;
  inline float value() const;
  inline void set_value(float value);
  
  // @@protoc_insertion_point(class_scope:l1menuprotobuf.Trigger.TriggerParameter)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_value();
  inline void clear_has_value();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* name_;
  float value_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_l1menu_2eproto();
  friend void protobuf_AssignDesc_l1menu_2eproto();
  friend void protobuf_ShutdownFile_l1menu_2eproto();
  
  void InitAsDefaultInstance();
  static Trigger_TriggerParameter* default_instance_;
};
// -------------------------------------------------------------------

class Trigger : public ::google::protobuf::Message {
 public:
  Trigger();
  virtual ~Trigger();
  
  Trigger(const Trigger& from);
  
  inline Trigger& operator=(const Trigger& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Trigger& default_instance();
  
  void Swap(Trigger* other);
  
  // implements Message ----------------------------------------------
  
  Trigger* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Trigger& from);
  void MergeFrom(const Trigger& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  typedef Trigger_TriggerParameter TriggerParameter;
  
  // accessors -------------------------------------------------------
  
  // required string name = 1;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 1;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  
  // required int32 version = 2;
  inline bool has_version() const;
  inline void clear_version();
  static const int kVersionFieldNumber = 2;
  inline ::google::protobuf::int32 version() const;
  inline void set_version(::google::protobuf::int32 value);
  
  // repeated .l1menuprotobuf.Trigger.TriggerParameter parameter = 3;
  inline int parameter_size() const;
  inline void clear_parameter();
  static const int kParameterFieldNumber = 3;
  inline const ::l1menuprotobuf::Trigger_TriggerParameter& parameter(int index) const;
  inline ::l1menuprotobuf::Trigger_TriggerParameter* mutable_parameter(int index);
  inline ::l1menuprotobuf::Trigger_TriggerParameter* add_parameter();
  inline const ::google::protobuf::RepeatedPtrField< ::l1menuprotobuf::Trigger_TriggerParameter >&
      parameter() const;
  inline ::google::protobuf::RepeatedPtrField< ::l1menuprotobuf::Trigger_TriggerParameter >*
      mutable_parameter();
  
  // repeated string varying_parameter = 4;
  inline int varying_parameter_size() const;
  inline void clear_varying_parameter();
  static const int kVaryingParameterFieldNumber = 4;
  inline const ::std::string& varying_parameter(int index) const;
  inline ::std::string* mutable_varying_parameter(int index);
  inline void set_varying_parameter(int index, const ::std::string& value);
  inline void set_varying_parameter(int index, const char* value);
  inline void set_varying_parameter(int index, const char* value, size_t size);
  inline ::std::string* add_varying_parameter();
  inline void add_varying_parameter(const ::std::string& value);
  inline void add_varying_parameter(const char* value);
  inline void add_varying_parameter(const char* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& varying_parameter() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_varying_parameter();
  
  // @@protoc_insertion_point(class_scope:l1menuprotobuf.Trigger)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_version();
  inline void clear_has_version();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* name_;
  ::google::protobuf::RepeatedPtrField< ::l1menuprotobuf::Trigger_TriggerParameter > parameter_;
  ::google::protobuf::RepeatedPtrField< ::std::string> varying_parameter_;
  ::google::protobuf::int32 version_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];
  
  friend void  protobuf_AddDesc_l1menu_2eproto();
  friend void protobuf_AssignDesc_l1menu_2eproto();
  friend void protobuf_ShutdownFile_l1menu_2eproto();
  
  void InitAsDefaultInstance();
  static Trigger* default_instance_;
};
// -------------------------------------------------------------------

class Event : public ::google::protobuf::Message {
 public:
  Event();
  virtual ~Event();
  
  Event(const Event& from);
  
  inline Event& operator=(const Event& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Event& default_instance();
  
  void Swap(Event* other);
  
  // implements Message ----------------------------------------------
  
  Event* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Event& from);
  void MergeFrom(const Event& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // repeated float threshold = 1;
  inline int threshold_size() const;
  inline void clear_threshold();
  static const int kThresholdFieldNumber = 1;
  inline float threshold(int index) const;
  inline void set_threshold(int index, float value);
  inline void add_threshold(float value);
  inline const ::google::protobuf::RepeatedField< float >&
      threshold() const;
  inline ::google::protobuf::RepeatedField< float >*
      mutable_threshold();
  
  // optional float weight = 2;
  inline bool has_weight() const;
  inline void clear_weight();
  static const int kWeightFieldNumber = 2;
  inline float weight() const;
  inline void set_weight(float value);
  
  // @@protoc_insertion_point(class_scope:l1menuprotobuf.Event)
 private:
  inline void set_has_weight();
  inline void clear_has_weight();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedField< float > threshold_;
  float weight_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_l1menu_2eproto();
  friend void protobuf_AssignDesc_l1menu_2eproto();
  friend void protobuf_ShutdownFile_l1menu_2eproto();
  
  void InitAsDefaultInstance();
  static Event* default_instance_;
};
// -------------------------------------------------------------------

class Run : public ::google::protobuf::Message {
 public:
  Run();
  virtual ~Run();
  
  Run(const Run& from);
  
  inline Run& operator=(const Run& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Run& default_instance();
  
  void Swap(Run* other);
  
  // implements Message ----------------------------------------------
  
  Run* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Run& from);
  void MergeFrom(const Run& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // repeated .l1menuprotobuf.Event event = 1;
  inline int event_size() const;
  inline void clear_event();
  static const int kEventFieldNumber = 1;
  inline const ::l1menuprotobuf::Event& event(int index) const;
  inline ::l1menuprotobuf::Event* mutable_event(int index);
  inline ::l1menuprotobuf::Event* add_event();
  inline const ::google::protobuf::RepeatedPtrField< ::l1menuprotobuf::Event >&
      event() const;
  inline ::google::protobuf::RepeatedPtrField< ::l1menuprotobuf::Event >*
      mutable_event();
  
  // @@protoc_insertion_point(class_scope:l1menuprotobuf.Run)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::l1menuprotobuf::Event > event_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_l1menu_2eproto();
  friend void protobuf_AssignDesc_l1menu_2eproto();
  friend void protobuf_ShutdownFile_l1menu_2eproto();
  
  void InitAsDefaultInstance();
  static Run* default_instance_;
};
// -------------------------------------------------------------------

class SampleHeader : public ::google::protobuf::Message {
 public:
  SampleHeader();
  virtual ~SampleHeader();
  
  SampleHeader(const SampleHeader& from);
  
  inline SampleHeader& operator=(const SampleHeader& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const SampleHeader& default_instance();
  
  void Swap(SampleHeader* other);
  
  // implements Message ----------------------------------------------
  
  SampleHeader* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SampleHeader& from);
  void MergeFrom(const SampleHeader& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // repeated .l1menuprotobuf.Trigger trigger = 1;
  inline int trigger_size() const;
  inline void clear_trigger();
  static const int kTriggerFieldNumber = 1;
  inline const ::l1menuprotobuf::Trigger& trigger(int index) const;
  inline ::l1menuprotobuf::Trigger* mutable_trigger(int index);
  inline ::l1menuprotobuf::Trigger* add_trigger();
  inline const ::google::protobuf::RepeatedPtrField< ::l1menuprotobuf::Trigger >&
      trigger() const;
  inline ::google::protobuf::RepeatedPtrField< ::l1menuprotobuf::Trigger >*
      mutable_trigger();
  
  // @@protoc_insertion_point(class_scope:l1menuprotobuf.SampleHeader)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::l1menuprotobuf::Trigger > trigger_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_l1menu_2eproto();
  friend void protobuf_AssignDesc_l1menu_2eproto();
  friend void protobuf_ShutdownFile_l1menu_2eproto();
  
  void InitAsDefaultInstance();
  static SampleHeader* default_instance_;
};
// ===================================================================


// ===================================================================

// Trigger_TriggerParameter

// required string name = 1;
inline bool Trigger_TriggerParameter::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Trigger_TriggerParameter::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Trigger_TriggerParameter::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Trigger_TriggerParameter::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& Trigger_TriggerParameter::name() const {
  return *name_;
}
inline void Trigger_TriggerParameter::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Trigger_TriggerParameter::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Trigger_TriggerParameter::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Trigger_TriggerParameter::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* Trigger_TriggerParameter::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// required float value = 2;
inline bool Trigger_TriggerParameter::has_value() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Trigger_TriggerParameter::set_has_value() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Trigger_TriggerParameter::clear_has_value() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Trigger_TriggerParameter::clear_value() {
  value_ = 0;
  clear_has_value();
}
inline float Trigger_TriggerParameter::value() const {
  return value_;
}
inline void Trigger_TriggerParameter::set_value(float value) {
  set_has_value();
  value_ = value;
}

// -------------------------------------------------------------------

// Trigger

// required string name = 1;
inline bool Trigger::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Trigger::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Trigger::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Trigger::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& Trigger::name() const {
  return *name_;
}
inline void Trigger::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Trigger::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Trigger::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Trigger::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* Trigger::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// required int32 version = 2;
inline bool Trigger::has_version() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Trigger::set_has_version() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Trigger::clear_has_version() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Trigger::clear_version() {
  version_ = 0;
  clear_has_version();
}
inline ::google::protobuf::int32 Trigger::version() const {
  return version_;
}
inline void Trigger::set_version(::google::protobuf::int32 value) {
  set_has_version();
  version_ = value;
}

// repeated .l1menuprotobuf.Trigger.TriggerParameter parameter = 3;
inline int Trigger::parameter_size() const {
  return parameter_.size();
}
inline void Trigger::clear_parameter() {
  parameter_.Clear();
}
inline const ::l1menuprotobuf::Trigger_TriggerParameter& Trigger::parameter(int index) const {
  return parameter_.Get(index);
}
inline ::l1menuprotobuf::Trigger_TriggerParameter* Trigger::mutable_parameter(int index) {
  return parameter_.Mutable(index);
}
inline ::l1menuprotobuf::Trigger_TriggerParameter* Trigger::add_parameter() {
  return parameter_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::l1menuprotobuf::Trigger_TriggerParameter >&
Trigger::parameter() const {
  return parameter_;
}
inline ::google::protobuf::RepeatedPtrField< ::l1menuprotobuf::Trigger_TriggerParameter >*
Trigger::mutable_parameter() {
  return &parameter_;
}

// repeated string varying_parameter = 4;
inline int Trigger::varying_parameter_size() const {
  return varying_parameter_.size();
}
inline void Trigger::clear_varying_parameter() {
  varying_parameter_.Clear();
}
inline const ::std::string& Trigger::varying_parameter(int index) const {
  return varying_parameter_.Get(index);
}
inline ::std::string* Trigger::mutable_varying_parameter(int index) {
  return varying_parameter_.Mutable(index);
}
inline void Trigger::set_varying_parameter(int index, const ::std::string& value) {
  varying_parameter_.Mutable(index)->assign(value);
}
inline void Trigger::set_varying_parameter(int index, const char* value) {
  varying_parameter_.Mutable(index)->assign(value);
}
inline void Trigger::set_varying_parameter(int index, const char* value, size_t size) {
  varying_parameter_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Trigger::add_varying_parameter() {
  return varying_parameter_.Add();
}
inline void Trigger::add_varying_parameter(const ::std::string& value) {
  varying_parameter_.Add()->assign(value);
}
inline void Trigger::add_varying_parameter(const char* value) {
  varying_parameter_.Add()->assign(value);
}
inline void Trigger::add_varying_parameter(const char* value, size_t size) {
  varying_parameter_.Add()->assign(reinterpret_cast<const char*>(value), size);
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
Trigger::varying_parameter() const {
  return varying_parameter_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
Trigger::mutable_varying_parameter() {
  return &varying_parameter_;
}

// -------------------------------------------------------------------

// Event

// repeated float threshold = 1;
inline int Event::threshold_size() const {
  return threshold_.size();
}
inline void Event::clear_threshold() {
  threshold_.Clear();
}
inline float Event::threshold(int index) const {
  return threshold_.Get(index);
}
inline void Event::set_threshold(int index, float value) {
  threshold_.Set(index, value);
}
inline void Event::add_threshold(float value) {
  threshold_.Add(value);
}
inline const ::google::protobuf::RepeatedField< float >&
Event::threshold() const {
  return threshold_;
}
inline ::google::protobuf::RepeatedField< float >*
Event::mutable_threshold() {
  return &threshold_;
}

// optional float weight = 2;
inline bool Event::has_weight() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Event::set_has_weight() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Event::clear_has_weight() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Event::clear_weight() {
  weight_ = 0;
  clear_has_weight();
}
inline float Event::weight() const {
  return weight_;
}
inline void Event::set_weight(float value) {
  set_has_weight();
  weight_ = value;
}

// -------------------------------------------------------------------

// Run

// repeated .l1menuprotobuf.Event event = 1;
inline int Run::event_size() const {
  return event_.size();
}
inline void Run::clear_event() {
  event_.Clear();
}
inline const ::l1menuprotobuf::Event& Run::event(int index) const {
  return event_.Get(index);
}
inline ::l1menuprotobuf::Event* Run::mutable_event(int index) {
  return event_.Mutable(index);
}
inline ::l1menuprotobuf::Event* Run::add_event() {
  return event_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::l1menuprotobuf::Event >&
Run::event() const {
  return event_;
}
inline ::google::protobuf::RepeatedPtrField< ::l1menuprotobuf::Event >*
Run::mutable_event() {
  return &event_;
}

// -------------------------------------------------------------------

// SampleHeader

// repeated .l1menuprotobuf.Trigger trigger = 1;
inline int SampleHeader::trigger_size() const {
  return trigger_.size();
}
inline void SampleHeader::clear_trigger() {
  trigger_.Clear();
}
inline const ::l1menuprotobuf::Trigger& SampleHeader::trigger(int index) const {
  return trigger_.Get(index);
}
inline ::l1menuprotobuf::Trigger* SampleHeader::mutable_trigger(int index) {
  return trigger_.Mutable(index);
}
inline ::l1menuprotobuf::Trigger* SampleHeader::add_trigger() {
  return trigger_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::l1menuprotobuf::Trigger >&
SampleHeader::trigger() const {
  return trigger_;
}
inline ::google::protobuf::RepeatedPtrField< ::l1menuprotobuf::Trigger >*
SampleHeader::mutable_trigger() {
  return &trigger_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace l1menuprotobuf

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_l1menu_2eproto__INCLUDED
