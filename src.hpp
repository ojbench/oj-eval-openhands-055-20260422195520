#include <iostream>
#include <algorithm>
#include "base.hpp"
using namespace std;

struct date {
    int year, month, day;
    date() = default;
    date(int y, int m, int d) : year(y), month(m), day(d) {}
};

static inline int __date_to_days(const date &dt){
    return dt.year * 360 + (dt.month - 1) * 30 + (dt.day - 1);
}

static inline bool __date_less(const date &a, const date &b){
    return __date_to_days(a) < __date_to_days(b);
}

istream& operator>>(istream& is, date& dt){
    return (is >> dt.year >> dt.month >> dt.day);
}

bool operator<(const date& a, const date& b){
    return __date_less(a,b);
}

class mail : public object {
protected:
    string postmark;
    date send_date;
    date arrive_date;
public:
    mail() = default;
    mail(string _contain_, string _postmark_, date send_d, date arrive_d) : object(_contain_), postmark(_postmark_), send_date(send_d), arrive_date(arrive_d) {}
    virtual ~mail() {}

    void copy(object* o) override {
        contain = reinterpret_cast<mail*>(o)->contain;
        postmark = reinterpret_cast<mail*>(o)->postmark;
        send_date = reinterpret_cast<mail*>(o)->send_date;
        arrive_date = reinterpret_cast<mail*>(o)->arrive_date;
    }

    string send_status(int, int, int) override { return "not send"; }
    string type() override { return "no type"; }
    void print() override {
        object::print();
        cout << "[mail] postmark: " << postmark << '\n';
    }
};

class air_mail : public mail {
protected:
    string airlines;
    date take_off_date;
    date land_date;
public:
    air_mail() = default;
    air_mail(string _contain_, string _postmark_, date send_d, date arrive_d, date take_off, date land, string _airline)
        : mail(_contain_, _postmark_, send_d, arrive_d), airlines(_airline), take_off_date(take_off), land_date(land) {}
    ~air_mail() override {}

    void copy(object* o) override {
        air_mail* p = reinterpret_cast<air_mail*>(o);
        contain = p->contain;
        postmark = p->postmark;
        send_date = p->send_date;
        arrive_date = p->arrive_date;
        airlines = p->airlines;
        take_off_date = p->take_off_date;
        land_date = p->land_date;
    }

    string send_status(int y, int m, int d) override {
        date ask_date(y,m,d);
        if (ask_date < send_date) return "mail not send";
        else if (ask_date < take_off_date) return "wait in airport";
        else if (ask_date < land_date) return "in flight";
        else if (ask_date < arrive_date) return "already land";
        else return "already arrive";
    }
    string type() override { return "air"; }
    void print() override {
        mail::print();
        cout << "[air] airlines: " << airlines << '\n';
    }
};

class train_mail : public mail {
protected:
    string* station_name = nullptr;
    date* station_time = nullptr;
    int len = 0;
public:
    train_mail() = default;
    train_mail(string _contain_, string _postmark_, date send_d, date arrive_d, string* sname, date* stime, int station_num)
        : mail(_contain_, _postmark_, send_d, arrive_d) {
        len = station_num;
        if (len > 0) {
            station_name = new string[len];
            station_time = new date[len];
            for (int i = 0; i < len; ++i) {
                station_name[i] = sname[i];
                station_time[i] = stime[i];
            }
        }
    }
    ~train_mail() override {
        delete[] station_name;
        delete[] station_time;
    }

    void copy(object* o) override {
        train_mail* p = reinterpret_cast<train_mail*>(o);
        contain = p->contain;
        postmark = p->postmark;
        send_date = p->send_date;
        arrive_date = p->arrive_date;
        delete[] station_name; station_name = nullptr;
        delete[] station_time; station_time = nullptr;
        len = p->len;
        if (len > 0) {
            station_name = new string[len];
            station_time = new date[len];
            for (int i = 0; i < len; ++i) {
                station_name[i] = p->station_name[i];
                station_time[i] = p->station_time[i];
            }
        }
    }

    string send_status(int y, int m, int d) override {
        date ask_date(y,m,d);
        if (ask_date < send_date) return "mail not send";
        if (!(ask_date < arrive_date)) return "already arrive";
        // equality with station times
        int lo = 0, hi = len - 1;
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            if (! (ask_date < station_time[mid]) && ! (station_time[mid] < ask_date)) {
                return string("in station ") + station_name[mid];
            }
            if (__date_less(station_time[mid], ask_date)) lo = mid + 1; else hi = mid - 1;
        }
        // At or before first station time
        if (len > 0 && (ask_date < station_time[0])) {
            return string("wait in station ") + station_name[0];
        }
        // Between station times
        if (len > 0) {
            // find first station_time > ask_date
            int L = 0, R = len - 1, pos = len;
            while (L <= R) {
                int mid = (L + R) >> 1;
                if (__date_less(ask_date, station_time[mid])) { pos = mid; R = mid - 1; }
                else L = mid + 1;
            }
            if (pos > 0 && pos < len) return "in train"; // between pos-1 and pos
            if (pos == len) {
                // after last station time but before arrive_date
                if (! (ask_date < arrive_date)) return "already arrive"; // equality handled above didn't match any station time
                return string("wait in station ") + station_name[len-1];
            }
        }
        // No stations provided
        if (! (ask_date < arrive_date)) return "already arrive";
        return "in train";
    }

    string type() override { return "train"; }
    void print() override {
        mail::print();
        cout << "[train] station_num: " << len << '\n';
    }
};

class car_mail : public mail {
protected:
    int total_mile = 0;
    string driver;
public:
    car_mail() = default;
    car_mail(string _contain_, string _postmark_, date send_d, date arrive_d, int mile, string _driver)
        : mail(_contain_, _postmark_, send_d, arrive_d), total_mile(mile), driver(_driver) {}
    ~car_mail() override {}

    void copy(object* o) override {
        car_mail* p = reinterpret_cast<car_mail*>(o);
        contain = p->contain;
        postmark = p->postmark;
        send_date = p->send_date;
        arrive_date = p->arrive_date;
        total_mile = p->total_mile;
        driver = p->driver;
    }

    string send_status(int y, int m, int d) override {
        date ask_date(y,m,d);
        if (ask_date < send_date) return "mail not send";
        if (__date_less(arrive_date, ask_date) || (! (ask_date < arrive_date) && ! (arrive_date < ask_date))) {
            return "already arrive";
        }
        double total_time = (double)(__date_to_days(arrive_date) - __date_to_days(send_date));
        double used_time = (double)(__date_to_days(ask_date) - __date_to_days(send_date));
        double current_mile = (used_time / total_time) * (double)total_mile;
        return to_string(current_mile);
    }

    string type() override { return "car"; }
    void print() override {
        mail::print();
        cout << "[car] driver_name: " << driver << '\n';
    }
};

void obj_swap(object *&lhs, object *&rhs){
    object* tmp = lhs;
    lhs = rhs;
    rhs = tmp;
}
