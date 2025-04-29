#include <bits/stdc++.h>
using namespace std;

// Node dari AVL Tree
struct Node {
    Node *left;
    Node *right;
    int key;
    int height;

    // Constructor default
    Node() {
        key = 0;
        height = 1;
        right = left = NULL;
    }

    // Constructor dengan parameter key
    Node(int _key) {
        key = _key;
        height = 1;
        left = right = NULL;
    }
};

struct AVL {
public:
    Node *root;

    // Mengambil tinggi node (0 jika NULL)
    int getHeight(Node *cur) {
        if (cur == NULL) return 0;
        return cur->height;
    }

    // Memperbarui tinggi suatu node
    Node *updateHeight(Node *cur) {
        if (cur == NULL) return cur;
        cur->height = 1 + max(getHeight(cur->left), getHeight(cur->right));
        return cur; // penting: harus return cur agar bisa dipakai chaining
    }

    // Menghitung balance factor suatu node
    int getBalance(Node *cur) {
        if (cur == NULL) return 0;
        return getHeight(cur->left) - getHeight(cur->right);
    }

    // Rotasi kiri untuk rebalancing
    Node *leftrotate(Node *y) {
        Node *x = y->right;
        Node *T2 = x->left;

        // Rotasi
        y->right = T2;
        updateHeight(y);

        x->left = y;
        updateHeight(x);

        return x;
    }

    // Rotasi kanan untuk rebalancing
    Node *rightrotate(Node *x) {
        Node *y = x->left;
        Node *T2 = y->right;

        // Rotasi
        x->left = T2;
        updateHeight(x);

        y->right = x;
        updateHeight(y);

        return y;
    }

    // Fungsi untuk memastikan AVL Tree tetap seimbang
    Node *rebalancing(Node *cur) {
        if (getBalance(cur) < -1) {
            // Kasus Right-Left
            if (getBalance(cur->right) > 0) {
                cur->right = rightrotate(cur->right);
            }
            // Kasus Right-Right
            return leftrotate(cur);
        } else if (getBalance(cur) > 1) {
            // Kasus Left-Right
            if (getBalance(cur->left) < 0) {
                cur->left = leftrotate(cur->left);
            }
            // Kasus Left-Left
            return rightrotate(cur);
        }
        return cur; // tidak perlu rotasi
    }

    // Menyisipkan key baru ke dalam AVL Tree
    Node *insert(Node *cur, int key) {
        if (cur == NULL) {
            return new Node(key); // buat node baru jika posisi kosong
        }

        if (key == cur->key) {
            return cur; // tidak menerima duplikat
        }

        if (key < cur->key) {
            cur->left = insert(cur->left, key); // rekursi ke kiri
        } else if (key > cur->key) {
            cur->right = insert(cur->right, key); // rekursi ke kanan
        }

        updateHeight(cur); // perbarui tinggi setelah penyisipan
        return rebalancing(cur); // jaga keseimbangan
    }

    // Menghapus node berdasarkan key
    Node *erase(Node *cur, int key) {
        if (cur == NULL) return cur;

        if (key < cur->key) {
            cur->left = erase(cur->left, key);
        } else if (key > cur->key) {
            cur->right = erase(cur->right, key);
        } else {
            // Kasus 1: Node adalah leaf
            if (cur->left == NULL && cur->right == NULL) {
                delete cur;
                return NULL;
            }
            // Kasus 2: Node memiliki dua anak
            else if (cur->left != NULL && cur->right != NULL) {
                int succ = findMin(cur->right); // cari nilai pengganti
                cur->key = succ;
                cur->right = erase(cur->right, succ);
            }
            // Kasus 3: Hanya punya satu anak
            else if (cur->left != NULL) {
                Node *temp = cur;
                cur = cur->left;
                delete temp;
            } else {
                Node *temp = cur;
                cur = cur->right;
                delete temp;
            }
        }

        updateHeight(cur);
        return rebalancing(cur);
    }

    // Mencari nilai minimum dalam subtree
    int findMin(Node *cur) {
        if (cur->left == NULL) return cur->key;
        return findMin(cur->left);
    }

    // Menampilkan isi tree (in-order traversal)
    void debug(Node *cur) {
        if (cur == NULL) return;
        debug(cur->left);
        cout << cur->key << "," << cur->height << " ";
        debug(cur->right);
    }

public:
    // Konstruktor AVL
    AVL() {
        root = NULL;
    }

    // Fungsi publik untuk insert
    void insert(int key) {
        root = insert(root, key);
    }

    // Fungsi publik untuk erase
    void erase(int key) {
        root = erase(root, key);
    }

    // Fungsi publik untuk debug
    void debug() {
        debug(root);
    }
};

int main() {
    AVL A;
    for (int i = 0; i < 100000; i++) A.insert(i); // menyisipkan 100 ribu angka
    for (int i = 0; i < 100000; i++) A.erase(i);  // menghapus semua angka

    return 0;
}
