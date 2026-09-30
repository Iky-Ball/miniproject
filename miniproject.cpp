#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// data global
const int jumlah_produk = 5;
// array nama produk
string namaProduk[jumlah_produk] = {"Nasi Goreng", "Mie Goreng", "Es Teh", "Kopi", "Air Mineral"};
// array harga produk
int hargaProduk[jumlah_produk] = {15000, 12000, 5000, 7000, 4000};
// array stok produk
int stokProduk[jumlah_produk] = {10, 15, 20, 8, 25};
// array jumlah produk yang dibeli
int jumlahPesanan[jumlah_produk] = {0, 0, 0, 0, 0};
// nama kasir
string namaKasir;

// prototylpe untuk function
void tampilkanMenu();
void tampilkanProduk();
void buatTransaksi();
void tampilkanKeranjang();

double hitungSubtotal();
double hitungDiskon(double subtotal);

// function overloading
double hitungTotal(double subtotal);
double hitungTotal(double subtotal, double diskon);

void checkout();
void pembayaran(double total);

void cetakStruk(
    double subtotal,
    double diskon,
    double total,
    double bayar,
    double kembalian
);

// function untuk menampilkan menu
void tampilkanMenu() {
    cout << "\n";
    cout << "============================================\n";
    cout << "              BAKOELKASIR\n";
    cout << "       SISTEM KASIR SEDERHANA UMKM\n";
    cout << "============================================\n";

    cout << "Kasir : " << namaKasir << endl;

    cout << "--------------------------------------------\n";
    cout << "1. Daftar Produk\n";
    cout << "2. Buat Transaksi\n";
    cout << "3. Lihat Keranjang\n";
    cout << "4. Checkout\n";
    cout << "5. Keluar\n";
    cout << "--------------------------------------------\n";
}

// function untuk menampilkan produk
void tampilkanProduk() {
    cout << "\n";
    cout << "============== DAFTAR PRODUK ===============\n";
    cout << left
         << setw(5)  << "No"
         << setw(20) << "Produk"
         << setw(15) << "Harga"
         << setw(10) << "Stok"
         << endl;
    cout << "---------------------------------------------\n";

    // for digunakan untuk mengulang data produk
    for (int i = 0; i < jumlah_produk; i++){
        // continue digunakan untuk melewati produk
        // jika stoknya habis
        if (stokProduk[i] == 0)
        {
            continue;
        }
        cout << left
             << setw(5) << i + 1
             << setw(20) << namaProduk[i]
             << "Rp" << setw(13) << hargaProduk[i]
             << setw(10) << stokProduk[i]
             << endl;
    }
    cout << "=============================================\n";
}

// function untuk membuat transaksi
void buatTransaksi() {
    char lanjut = 'y';
    // while digunakan agar kasir dapat
    // memasukkan beberapa produk
    while (lanjut == 'y' || lanjut == 'Y'){
        tampilkanProduk();
        int pilihan;
        int jumlah;
        cout << "\nMasukkan nomor produk : ";
        cin >> pilihan;
        // if untuk validasi nomor produk
        if (pilihan < 1 || pilihan > jumlah_produk){
            cout << "Produk tidak ditemukan!\n";
            // continue kembali ke awal while
            continue;
        }

        // nomor produk dikurangi 1
        // agar sesuai dengan index array
        int index = pilihan - 1;

        // mengecek stok
        if (stokProduk[index] <= 0){
            cout << "Maaf, stok produk habis!\n";
            continue;
        }

        cout << "Produk : " << namaProduk[index] << endl;
        cout << "Masukkan jumlah : ";
        cin >> jumlah;

        // validasi jumlah
        if (jumlah <= 0){
            cout << "Jumlah harus lebih dari 0!\n";
            continue;
        }

        // mengecek apakah stok mencukupi
        if (jumlah > stokProduk[index]){
            cout << "Stok tidak mencukupi!\n";
            cout << "Stok tersedia : "<< stokProduk[index] << endl;
            continue;
        }

        // menambahkan jumlah produk ke keranjang
        jumlahPesanan[index] += jumlah;

        // mengurangi stok
        stokProduk[index] -= jumlah;

        cout << "\nPesanan berhasil ditambahkan!\n";
        cout << namaProduk[index]
             << " x"
             << jumlah
             << endl;
        cout << "\nTambah produk lain? (y/n): ";
        cin >> lanjut;
    }
}

// function untuk menampilkan keranjang
void tampilkanKeranjang() {
    bool adaPesanan = false;
    cout << "\n";
    cout << "=============== KERANJANG ==================\n";
    cout << left
         << setw(20) << "Produk"
         << setw(8)  << "Qty"
         << setw(15) << "Harga"
         << setw(15) << "Subtotal"
         << endl;
    cout << "---------------------------------------------\n";

    // for untuk mengecek semua produk
    for (int i = 0; i < jumlah_produk; i++) {
        // jika produk tidak dibeli
        // maka dilewati
        if (jumlahPesanan[i] == 0){
            continue;
        }

        adaPesanan = true;
        int subtotalProduk =
            jumlahPesanan[i] * hargaProduk[i];
        cout << left
             << setw(20) << namaProduk[i]
             << setw(8) << jumlahPesanan[i]
             << "Rp" << setw(13) << hargaProduk[i]
             << "Rp" << subtotalProduk
             << endl;
    }

    cout << "---------------------------------------------\n";

    if (!adaPesanan){
        cout << "Keranjang masih kosong.\n";
    }
    else {
        cout << "Subtotal : Rp"
             << hitungSubtotal()
             << endl;
    }
    cout << "=============================================\n";
}

// function untuk menghitung subtotal
double hitungSubtotal(){
    double subtotal = 0;
    for (int i = 0; i < jumlah_produk; i++){
        subtotal +=
            jumlahPesanan[i] * hargaProduk[i];
    }
    return subtotal;
}

// function untuk menghitung diskon
double hitungDiskon(double subtotal){
    double diskon = 0;
    // jika belanja minimal Rp50.000
    // mendapatkan diskon 10%
    if (subtotal >= 50000){
        diskon = subtotal * 0.10;
    } else{
        diskon = 0;
    }
    return diskon;
}

// function untuk overloading 1
// digunakan jika tidak ada diskon
double hitungTotal(double subtotal){
    return subtotal;
}

// function untuk overloading 2
// digunakan jika terdapat diskon
double hitungTotal(double subtotal, double diskon){
    return subtotal - diskon;
}

// function untuk checkout
void checkout(){
    double subtotal = hitungSubtotal();
    // mengecek apakah keranjang kosong
    if (subtotal == 0){
        cout << "\nKeranjang masih kosong!\n";
        cout << "Silakan buat transaksi terlebih dahulu.\n";
        return;
    }

    double diskon = hitungDiskon(subtotal);
    double total;

    // function overloading
    if (diskon > 0){
        total = hitungTotal(subtotal, diskon);
    } else{
        total = hitungTotal(subtotal);
    }
    cout << "\n";
    cout << "=============== CHECKOUT ==================\n";
    cout << "Subtotal : Rp" << subtotal << endl;
    cout << "Diskon   : Rp" << diskon << endl;
    cout << "--------------------------------------------\n";
    cout << "TOTAL    : Rp" << total << endl;
    cout << "============================================\n";
    pembayaran(total);
}

// function untuk pembayaran
void pembayaran(double total){
    double bayar;
    double kembalian;

    // while digunakan agar pembayaran
    // dapat diulang jika uang kurang
    while (true){
        cout << "\nMasukkan uang pembayaran : Rp";
        cin >> bayar;
        if (bayar >= total){
            // menghitung kembalian
            kembalian = bayar - total;
            cout << "\nPembayaran berhasil!\n";
            cout << "Kembalian : Rp" << kembalian << endl;

            double subtotal = hitungSubtotal();
            double diskon = hitungDiskon(subtotal);

            // cetak struk
            cetakStruk(subtotal, diskon, total, bayar, kembalian);
            // break digunakan untuk menghentikan while
            break;
        } else{
            cout << "\nUang pembayaran tidak mencukupi!\n";
            cout << "Total yang harus dibayar : Rp" << total << endl;
            cout << "Silakan masukkan uang kembali.\n";
        }
    }
}

// function untuk cetak struk
void cetakStruk(
    double subtotal,
    double diskon,
    double total,
    double bayar,
    double kembalian
){
    cout << "\n";
    cout << "============================================\n";
    cout << "              BAKOELKASIR\n";
    cout << "              STRUK BELANJA\n";
    cout << "============================================\n";
    cout << "Kasir : " << namaKasir << endl;
    cout << "--------------------------------------------\n";

    // for untuk menampilkan produk yang dibeli
    for (int i = 0; i < jumlah_produk; i++){
        if (jumlahPesanan[i] == 0){
            continue;
        }
        int subtotalProduk = jumlahPesanan[i] * hargaProduk[i];
        cout << left
             << setw(18) << namaProduk[i]
             << "x"
             << setw(4) << jumlahPesanan[i]
             << "Rp"
             << subtotalProduk
             << endl;
    }
    cout << "--------------------------------------------\n";
    cout << "Subtotal     : Rp" << subtotal << endl;
    cout << "Diskon       : Rp" << diskon << endl;
    cout << "Total        : Rp" << total << endl;
    cout << "Bayar        : Rp" << bayar << endl;
    cout << "Kembalian    : Rp" << kembalian << endl;
    cout << "============================================\n";
    cout << "          TERIMA KASIH!\n";
    cout << "       Selamat datang kembali\n";
    cout << "============================================\n";

    // mengosongkan keranjang setelah transaksi selesai
    for (int i = 0; i < jumlah_produk; i++){
        jumlahPesanan[i] = 0;
    }
}

// program utama
int main() {
    // variable scope
    // pilihan hanya dapat digunakan di dalam main()
    int pilihan = 0;
    cout << "============================================\n";
    cout << "          SELAMAT DATANG DI\n";
    cout << "              BAKOELKASIR\n";
    cout << "============================================\n";
    // masukkan nama kasir
    cout << "Masukkan nama kasir : ";
    getline(cin, namaKasir);

    // while untuk menjalankan menu sampai user memilih angka 5
    while (pilihan != 5){
        tampilkanMenu();
        cout << "Pilih menu : ";
        cin >> pilihan;

        // switch case untuk menentukan fitur yang dipilih
        switch (pilihan) {
            case 1:
                tampilkanProduk();
                break;
            case 2:
                buatTransaksi();
                break;
            case 3:
                tampilkanKeranjang();
                break;
            case 4:
                checkout();
                break;
            case 5:
                cout << "\nTerima kasih, " << namaKasir << "!\n";
                cout << "Program selesai.\n";
                break;
            default:
                cout << "\nPilihan tidak tersedia!\n";
                cout << "Silakan pilih menu 1-5.\n";
        }
    }
}
