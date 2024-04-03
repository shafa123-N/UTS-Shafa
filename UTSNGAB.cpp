#include <iostream>
#include <string>
using namespace std;

struct Mahasiswa {
    string Nama;
    int Nilai;
    Mahasiswa* next;
    Mahasiswa* prev;
};

Mahasiswa* head = nullptr;
Mahasiswa* tail = nullptr;

void tambahMahasiswa(string nama, int nilai) {
    Mahasiswa* baru = new Mahasiswa{nama, nilai, nullptr, nullptr};

    if (head == nullptr) {
        head = baru;
        tail = baru;
    } else {
        tail->next = baru;
        baru->prev = tail;
        tail = baru;
    }
}

void editMahasiswa(string nama, int nilaiBaru) {
    Mahasiswa* curr = head;
    while (curr != nullptr) {
        if (curr->Nama == nama) {
            curr->Nilai = nilaiBaru;
            cout << "Nilai untuk " << nama << " telah diupdate menjadi " << nilaiBaru << endl;
            return;
        }
        curr = curr->next;
    }
    cout << "Mahasiswa dengan nama " << nama << " tidak ditemukan." << endl;
}

void hapusMahasiswa(string nama) {
    Mahasiswa* curr = head;
    while (curr != nullptr) {
        if (curr->Nama == nama) {
            if (curr == head) {
                head = curr->next;
                if (head != nullptr) {
                    head->prev = nullptr;
                }
            } else if (curr == tail) {
                tail = curr->prev;
                tail->next = nullptr;
            } else {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
            }

            delete curr;
            cout << "Mahasiswa " << nama << " telah dihapus." << endl;
            return;
        }
        curr = curr->next;
    }
    cout << "Mahasiswa dengan nama " << nama << " tidak ditemukan." << endl;
}

void tampilkanMahasiswa() {
    Mahasiswa* curr = head;
    cout << "\nData Mahasiswa:" << endl;
    cout << "------------------------" << endl;
    cout << "|Nama\t\t| Nilai\t|" << endl;
    cout << "------------------------" << endl;
    while (curr != nullptr) {
        cout << "|" << curr->Nama << "\t\t|" << curr->Nilai << "\t|" << endl;
        curr = curr->next;
    }
    cout << "------------------------" << endl;
}

int main() {
    string nama;
    int nilai;
    char pilihan;

    do {
        cout << "\nMenu:" << endl;
        cout << "1. Tambah Mahasiswa" << endl;
        cout << "2. Edit Mahasiswa" << endl;
        cout << "3. Hapus Mahasiswa" << endl;
        cout << "4. Tampilkan Mahasiswa" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case '1':
                cout << "Masukkan nama mahasiswa: ";
                getline(cin, nama);
                cout << "Masukkan nilai mahasiswa: ";
                cin >> nilai;
                tambahMahasiswa(nama, nilai);
                break;
            case '2':
                cout << "Masukkan nama mahasiswa untuk diedit: ";
                getline(cin, nama);
                cout << "Masukkan nilai baru: ";
                cin >> nilai;
                editMahasiswa(nama, nilai);
                break;
            case '3':
                cout << "Masukkan nama mahasiswa untuk dihapus: ";
                getline(cin, nama);
                hapusMahasiswa(nama);
                break;
            case '4':
                tampilkanMahasiswa();
                break;
            case '5':
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != '5');

    // Cleanup
    while (head != nullptr) {
        Mahasiswa* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
