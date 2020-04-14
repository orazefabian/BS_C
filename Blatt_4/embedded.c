#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EEPROM_SIZE 1024
#define MAX_KEY 8190
#define MAX_VALUE 524286


typedef uint32_t Item;   ///< 32 bits: Single element of the array.
typedef unsigned Index;  ///< Index in the array.

/// A single item:
///
typedef uint16_t Key;     ///< Key for a given value in the range [0..8190].
typedef uint32_t Value;   ///< Even value in the range [0..524286].
typedef uint8_t  Parity;  ///< Parity bit (NOTE: No need to implement the calculation, just set it to zero).


/// Writes the given `key` and `value` to `memory` at the given `index`.
///
void setValue(Item* memory, Index index, Key key, Value value)
{
    // TODO
}


/// Returns the `value` at the given `index` from `memory`.
/// Writes the key to `key` if `key` != NULL.
///
Value getValue(Item* memory, Index index, Key* key)
{
    // TODO
}


/// If all bits for a given item are set, it is invalid (initial EEPROM state).
///
bool isValid(Item* memory, Index index)
{
    // TODO
}


// DO NOT MODIFY anything below.
//
int main(int argc, char** argv)
{
    Item* eeprom = (Item*) malloc(EEPROM_SIZE * sizeof(Item));
    assert(eeprom && "Memory allocation failed");
    memset(eeprom, 0xFF, EEPROM_SIZE * sizeof(Item));

    // test cases
    //
    Index index = 13;
    assert(!isValid(eeprom, index));

    Key   key   = 26;
    Value value = 28;
    setValue(eeprom, index, key, value);
    setValue(eeprom, index + 1, key + 1, value + 2);

    Key retkey = 0;
    assert(value == getValue(eeprom, index, NULL));
    assert(value + 2 == getValue(eeprom, index + 1, &retkey));
    assert(retkey == key + 1);
    assert(isValid(eeprom, index));

    // test lower limits
    //
    key   = 0;
    value = 1;
    setValue(eeprom, index, key, value);
    assert(0 == getValue(eeprom, index, &retkey));
    assert(key == retkey);

    // test upper limits
    //
    key   = MAX_KEY;  // NOTE: all bits set for key == invalid item
    value = MAX_VALUE;
    setValue(eeprom, index, key, value);
    assert(value == getValue(eeprom, index, &retkey));
    assert(key == retkey);

    // test above upper limits
    //
    key   = MAX_KEY + 2;  // NOTE: all bits set for key == invalid item
    value = MAX_VALUE + 2;
    setValue(eeprom, index, key, value);
    assert(0 == getValue(eeprom, index, &retkey));
    assert(0 == retkey);

    assert(!isValid(eeprom, EEPROM_SIZE));

    free(eeprom);
    printf("Tests passed.\n");
    return 0;
}
