
varargs mixed *select_many(mixed *arr, function f, mixed args...);

varargs mixed *select_many(mixed *arr, function f, mixed args...) {
    mixed *result = ({ });
    mixed i;

    foreach (i in arr) {
        result += evaluate(f, i, args...);
    }

    return result;
}
