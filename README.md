# Variant

Simple **boost::any** analog (c++11).

Short example:
```
Variant v;
v = 10;
if (v.isType<int>())
    cout << v.value<int>() << endl;
```

Variant supports compare opeartions if it supported by holded value.
So it can be used in **std::set** like containers.

*(c) 2015 Vladislav Navrocky*