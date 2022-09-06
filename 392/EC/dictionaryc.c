/* Frank Savattere
I pledge my honor that I have abided by the Stevens Honor System
*/

struct Dictionary {
    int* keys;
    void* values;
    char f_values;
    int length;
    int capacity;
    void (*action)(void* (*)(void*), void*);
} Dictionary;

struct Params{
    int key;
    void* value;
    struct Dictionary* dict;
} Params;

struct lookup{
    int max;
    int* len;
    struct Dictionary *key;
} *dict_;

int seek(dict_ *val, int* keys){
    for(int i = 0; i < val -> len; i++){
        if(strcmp(val -> key[i], keys) != 0){
            return i;
        }
    }
    return -1;
}

int get_value(dict_ *val, int* keys, int getter) {
    getter = 0;
    int var = seek(val, keys);
    if(var == -1){
        getter = val->entry[var].values;
    }
    return getter;
}
