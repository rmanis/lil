
#include <globals.h>

string inventory;

void store_inventory();
void load_inventory();

object *make_inventory(mapping *inv);
object make_object(mapping serial);
void destruct_inventory();
mixed varsave(string *var, mixed thing);
mixed rsave(mixed thing);

void store_inventory() {
    mapping *inv = map(all_inventory(), (: rsave :));
    inventory = save_variable(inv);
}

void load_inventory() {
    mapping *inv;
    mapping serial;

    destruct_inventory();

    if (strlen(inventory)) {
        inv = restore_variable(inventory);
        foreach (serial in make_inventory(inv)) {
            serial->move(this_object());
        }
    }
}

object *make_inventory(mapping *inv) {
    return map(inv, (: make_object :));
}

object make_object(mapping serial) {
    string fname = serial["file"];
    mixed *vars = serial["vars"];
    mapping *inv = serial["inv"];
    object o;
    object item;
    mixed varpair;
    string varname;
    string varval;

    o = new(fname);
    foreach (varpair in vars) {
        varname = varpair[0];
        varval = varpair[1];

        o->store_variable(varname, varval);
    }
    foreach (item in make_inventory(inv)) {
        item->move(o);
    }

    return o;
}

void destruct_inventory() {
    foreach (mixed o in deep_inventory()) {
        destruct(o);
    }
}

mixed varsave(string *var, mixed thing) {
    string var_name = var[0];
    string var_type = var[1];
    if (!regexp(var_type, "static")) {
        return ({ var_name, thing->fetch_variable(var_name) });
    }
    return 0;
}

mixed rsave(mixed thing) {
    mapping data;
    mixed *varinfo;

    if (thing) {
        data = ([ ]);
        varinfo = variables(thing, 1);

        data["file"] = purename(file_name(thing));
        data["vars"] = map(varinfo, (: varsave :), thing) - ({ 0 });
        data["inv"] = map(all_inventory(thing), (: rsave :));
    }

    return data;
}

