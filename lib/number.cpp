#include "number.h"
#include <bitset>
#include <cmath>

uint239_t FromInt(uint32_t value, uint32_t shift) {

    uint239_t Number;
    for (int i = 0; i < 35; i++)
        Number.data[i] = 0;

    int binary_value_arr[245] = {0};
    int binary_shift_arr[35] = {0};
    int true_shift = shift;
    int i_v = 244;

    while (value > 0) {
        binary_value_arr[i_v] = value % 2;
        value /= 2;
        i_v--; 
    }

    Left_Shift(binary_value_arr, true_shift);

    int i_s = 34;

    while (shift > 0) {
        binary_shift_arr[i_s] = shift % 2;
        shift /= 2;
        i_s--; 
    }

    for (int i = 244; i >= 0; i--){
        if (binary_value_arr[i] == 1){
            int byte_index = i / 7; 
            int bit_index = 6-(i % 7);
            Number.data[byte_index] |= (1 << bit_index); 
        }
    }

    for (int i = 34; i >= 0; i--) {
        if (binary_shift_arr[i] == 1) {
            int byte_index = i;
            Number.data[byte_index] |= (1 << 7); 
        }
    }

    return Number;
}

uint239_t FromString(const char* str, uint32_t shift){
    uint64_t value = std::stoull(str);

    uint239_t Number;
    for (int i = 0; i < 35; i++)
        Number.data[i] = 0;

    int binary_value_arr[245] = {0};
    int binary_shift_arr[35] = {0};
    int true_shift = shift;

    int i_v = 244;

    while (value > 0) {
        binary_value_arr[i_v] = value % 2;
        value /= 2;
        i_v--; 
    }

    Left_Shift(binary_value_arr, true_shift);

    int i_s = 34;

    while (shift > 0) {
        binary_shift_arr[i_s] = shift % 2;
        shift /= 2;
        i_s--; 
    }

    for (int i = 244; i >= 0; i--){
        if (binary_value_arr[i] == 1){
            int byte_index = i / 7; 
            int bit_index = 6-(i % 7);
            Number.data[byte_index] |= (1 << bit_index); 
        }
    }

    for (int i = 34; i >= 0; i--) {
        if (binary_shift_arr[i] == 1) {
            int byte_index = i;
            Number.data[byte_index] |= (1 << 7); 
    }
}

    return Number;

}

uint239_t operator+(const uint239_t& lhs, const uint239_t& rhs){


    uint64_t res_shift = GetShift(lhs) + GetShift(rhs);

    uint64_t shift = res_shift;

    int binary_shift_arr[35] = {0};

    int i_s = 34;

    while (shift > 0) {
        binary_shift_arr[i_s] = shift % 2;
        shift /= 2;
        i_s--; 
    }



    int lhs_arr[245] = {0};
    int rhs_arr[245] = {0};

    for (int i = 0; i < 245; i++) {
        
        int byte_index = i / 7;
        int bit_index = 6 - (i % 7);
        lhs_arr[i] = (lhs.data[byte_index] >> bit_index) & 1; 
        rhs_arr[i] = (rhs.data[byte_index] >> bit_index) & 1; 
    }

    Right_Shift(lhs_arr, GetShift(lhs));
    Right_Shift(rhs_arr, GetShift(rhs));

    uint239_t lhs_rigt_shift;
    uint239_t rhs_rigt_shift;

    for (int i = 0; i < 35; i++){
        lhs_rigt_shift.data[i] = 0;
        rhs_rigt_shift.data[i] = 0;
    }

    for (int i = 244; i >= 0; i--){

        if (lhs_arr[i] == 1){
            int byte_index = i / 7; 
            int bit_index = 6-(i % 7);
            lhs_rigt_shift.data[byte_index] |= (1 << bit_index); 
        }

        if (rhs_arr[i] == 1){
            int byte_index = i / 7; 
            int bit_index = 6-(i % 7);
            rhs_rigt_shift.data[byte_index] |= (1 << bit_index); 
        }

    }

    uint239_t result;
    uint16_t carry = 0;

    for (int byte = 34; byte >= 0; byte--){

        if (lhs_rigt_shift.data[byte] + rhs_rigt_shift.data[byte] + carry > 127){

            result.data[byte] = lhs_rigt_shift.data[byte] + rhs_rigt_shift.data[byte] + carry - 128;
            carry = 1;

        }else{

            result.data[byte] = lhs_rigt_shift.data[byte] + rhs_rigt_shift.data[byte] + carry;
            carry = 0;

        }

    }

    int result_arr[245] = {0};

    for (int i = 0; i < 245; i++) {
        
        int byte_index = i / 7;
        int bit_index = 6 - (i % 7);
        result_arr[i] = (result.data[byte_index] >> bit_index) & 1;

    }

    Left_Shift(result_arr, res_shift);

    uint239_t return_result;
    for (int i = 0; i < 35; i++)
        return_result.data[i] = 0;

    for (int i = 244; i >= 0; i--){
        if (result_arr[i] == 1){
            int byte_index = i / 7; 
            int bit_index = 6-(i % 7);
            return_result.data[byte_index] |= (1 << bit_index); 
        }
    }
    
    for (int i = 34; i >= 0; i--) {
        if (binary_shift_arr[i] == 1) {
            int byte_index = i;
            return_result.data[byte_index] |= (1 << 7); 
        }
    }


    return return_result;
}

uint239_t operator-(const uint239_t& lhs, const uint239_t& rhs){

    uint64_t res_shift = GetShift(lhs) - GetShift(rhs);

    if (res_shift < 0)
        res_shift = pow(2,35) - res_shift;

    uint64_t shift = res_shift;

    int binary_shift_arr[35] = {0};

    int i_s = 34;

    while (shift > 0) {
        binary_shift_arr[i_s] = shift % 2;
        shift /= 2;
        i_s--; 
    }


    int lhs_arr[245] = {0};
    int rhs_arr[245] = {0};

    for (int i = 0; i < 245; i++) {
        
        int byte_index = i / 7;
        int bit_index = 6 - (i % 7);
        lhs_arr[i] = (lhs.data[byte_index] >> bit_index) & 1; 
        rhs_arr[i] = (rhs.data[byte_index] >> bit_index) & 1; 
    }

    Right_Shift(lhs_arr, GetShift(lhs));
    Right_Shift(rhs_arr, GetShift(rhs));

    uint239_t lhs_rigt_shift;
    uint239_t rhs_rigt_shift;

    for (int i = 0; i < 35; i++){
        lhs_rigt_shift.data[i] = 0;
        rhs_rigt_shift.data[i] = 0;
    }

    for (int i = 244; i >= 0; i--){

        if (lhs_arr[i] == 1){
            int byte_index = i / 7; 
            int bit_index = 6-(i % 7);
            lhs_rigt_shift.data[byte_index] |= (1 << bit_index); 
        }

        if (rhs_arr[i] == 1){
            int byte_index = i / 7; 
            int bit_index = 6-(i % 7);
            rhs_rigt_shift.data[byte_index] |= (1 << bit_index); 
        }

    }

    uint239_t result;
    uint16_t borrow = 0;

    for (int byte = 34; byte >= 0; byte--){

        if (lhs_rigt_shift.data[byte] - rhs_rigt_shift.data[byte] - borrow < 0){

            result.data[byte] = lhs_rigt_shift.data[byte] - rhs_rigt_shift.data[byte] - borrow + 128;
            borrow = 1;

        }else{

            result.data[byte] = lhs_rigt_shift.data[byte] - rhs_rigt_shift.data[byte] - borrow;
            borrow = 0;

        }

    }

    int result_arr[245] = {0};

    for (int i = 0; i < 245; i++) {
        
        int byte_index = i / 7;
        int bit_index = 6 - (i % 7);
        result_arr[i] = (result.data[byte_index] >> bit_index) & 1;

    }

    Left_Shift(result_arr, res_shift);

    uint239_t return_result;
    for (int i = 0; i < 35; i++)
        return_result.data[i] = 0;

    for (int i = 244; i >= 0; i--){
        if (result_arr[i] == 1){
            int byte_index = i / 7; 
            int bit_index = 6-(i % 7);
            return_result.data[byte_index] |= (1 << bit_index); 
        }
    }
    
    for (int i = 34; i >= 0; i--) {
        if (binary_shift_arr[i] == 1) {
            int byte_index = i;
            return_result.data[byte_index] |= (1 << 7); 
        }
    }


    return return_result;

}

bool operator==(const uint239_t& lhs, const uint239_t& rhs){

    int shift_lhs = GetShift(lhs);
    int shift_rhs = GetShift(rhs);

    int lhs_arr[245] = {0};
    int rhs_arr[245] = {0};

    for (int i = 0; i < 245; i++) {
        int byte_index = i / 7;
        int bit_index = 6 - (i % 7);
        lhs_arr[i] = (lhs.data[byte_index] >> bit_index) & 1; ; 
    }

    for (int i = 0; i < 245; i++) {
        int byte_index = i / 7;
        int bit_index = 6 - (i % 7);
        rhs_arr[i] = (rhs.data[byte_index] >> bit_index) & 1; 
    }

    Right_Shift(lhs_arr, shift_lhs);
    Right_Shift(rhs_arr, shift_rhs);

    int count = 0;

    for (int j = 0; j < 245; j++){
        
        if (lhs_arr[j] == rhs_arr[j])
            count++;

    }

    if (count == 245){
        return true;
    }else{
        return false;
    }

}

bool operator!=(const uint239_t& lhs, const uint239_t& rhs){

    int shift_lhs = GetShift(lhs);
    int shift_rhs = GetShift(rhs);

    int lhs_arr[245] = {0};
    int rhs_arr[245] = {0};

    for (int i = 0; i < 245; i++) {
        int byte_index = i / 7;
        int bit_index = 6 - (i % 7);
        lhs_arr[i] = (lhs.data[byte_index] >> bit_index) & 1; ; 
    }

    for (int i = 0; i < 245; i++) {
        int byte_index = i / 7;
        int bit_index = 6 - (i % 7);
        rhs_arr[i] = (rhs.data[byte_index] >> bit_index) & 1; 
    }

    Right_Shift(lhs_arr, shift_lhs);
    Right_Shift(rhs_arr, shift_rhs);

    int count = 0;

    for (int j = 0; j < 245; j++){
        
        if (lhs_arr[j] == rhs_arr[j])
            count++;

    }

    if (count == 245){
        return false;
    }else{
        return true;
    }

}

std::ostream& operator<<(std::ostream& stream, const uint239_t& value) {

    for (int i = 0; i <35; ++i) {

        uint8_t byte = value.data[i];

        for (int bit = 7; bit >= 0; --bit) {

            stream << ((byte >> bit) & 1);

        }
    } 
    return stream;
}

uint64_t GetShift(const uint239_t& value){

    uint64_t shift = 0;
    for (int i = 34; i >= 0; --i) {
        if (value.data[i] & 128) {
            shift += pow(2, (34 - i));
        }
    }

    return shift;
}

void Left_Shift(int binary_value_arr[], uint32_t shift){

    int true_shift = shift % 245;
   
    int count = 0;
    while (count < true_shift) {
        int first = binary_value_arr[0];
        for (int i = 1; i < 245; ++i)
            binary_value_arr[i - 1] = binary_value_arr[i];
        binary_value_arr[244] = first;
        count += 1;
    }
    
}

void Right_Shift(int binary_value_arr[], uint32_t shift){

    int true_shift = shift % 245;

    int count = 0;
    while (count < true_shift ) {
        int last = binary_value_arr[244];
        for (int i = 244; i > 0; --i)
            binary_value_arr[i] = binary_value_arr[i - 1];
        binary_value_arr[0] = last;
        count += 1;
            
    }
    
}
