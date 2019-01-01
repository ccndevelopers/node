// Copyright 2017 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_OBJECTS_JS_COLLECTION_INL_H_
#define V8_OBJECTS_JS_COLLECTION_INL_H_

#include "src/objects/js-collection.h"

#include "src/objects-inl.h"  // Needed for write barriers

// Has to be the last include (doesn't have include guards):
#include "src/objects/object-macros.h"

namespace v8 {
namespace internal {

OBJECT_CONSTRUCTORS_IMPL(JSCollection, JSObject)
OBJECT_CONSTRUCTORS_IMPL(JSMap, JSCollection)
OBJECT_CONSTRUCTORS_IMPL(JSSet, JSCollection)
OBJECT_CONSTRUCTORS_IMPL(JSWeakCollection, JSObject)
OBJECT_CONSTRUCTORS_IMPL(JSWeakMap, JSWeakCollection)
OBJECT_CONSTRUCTORS_IMPL(JSWeakSet, JSWeakCollection)

// TODO(jkummerow): Move JSCollectionIterator to js-collection.h?
// TODO(jkummerow): Introduce IsJSCollectionIterator() check? Or unchecked
// version of OBJECT_CONSTRUCTORS_IMPL macro?
JSCollectionIterator::JSCollectionIterator(Address ptr) : JSObject(ptr) {}
template <class Derived, class TableType>
OrderedHashTableIterator<Derived, TableType>::OrderedHashTableIterator(
    Address ptr)
    : JSCollectionIterator(ptr) {}

JSMapIterator::JSMapIterator(Address ptr)
    : OrderedHashTableIterator<JSMapIterator, OrderedHashMap>(ptr) {
  SLOW_DCHECK(IsJSMapIterator());
}

JSSetIterator::JSSetIterator(Address ptr)
    : OrderedHashTableIterator<JSSetIterator, OrderedHashSet>(ptr) {
  SLOW_DCHECK(IsJSSetIterator());
}

ACCESSORS(JSCollection, table, Object, kTableOffset)
ACCESSORS(JSCollectionIterator, table, Object, kTableOffset)
ACCESSORS(JSCollectionIterator, index, Object, kIndexOffset)

ACCESSORS(JSWeakCollection, table, Object, kTableOffset)

CAST_ACCESSOR2(JSSet)
CAST_ACCESSOR2(JSSetIterator)
CAST_ACCESSOR2(JSMap)
CAST_ACCESSOR2(JSMapIterator)
CAST_ACCESSOR2(JSWeakCollection)
CAST_ACCESSOR2(JSWeakMap)
CAST_ACCESSOR2(JSWeakSet)

Object JSMapIterator::CurrentValue() {
  OrderedHashMap table = OrderedHashMap::cast(this->table());
  int index = Smi::ToInt(this->index());
  Object value = table->ValueAt(index);
  DCHECK(!value->IsTheHole());
  return value;
}

}  // namespace internal
}  // namespace v8

#include "src/objects/object-macros-undef.h"

#endif  // V8_OBJECTS_JS_COLLECTION_INL_H_
