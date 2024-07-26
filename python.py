import rsa
from rsa.key import PublicKey, PrivateKey

# Misalkan Anda memiliki nilai e, d, dan n
e = 7  # Biasanya nilai e umum
d = 103 # Nilai d yang sesuai dengan e dan n
n = 143 # Nilai n yang besar (hasil dari p * q)

# Membuat objek kunci publik dan privat
public_key = PublicKey(n, e)
private_key = PrivateKey(n, e, d, 11, 13)

# Enkripsi pesan
message = 'hello'.encode('utf8')
encrypted_message = rsa.encrypt(message, public_key)
print('Encrypted:', encrypted_message)

# Dekripsi pesan
decrypted_message = rsa.decrypt(encrypted_message, private_key).decode('utf8')
print('Decrypted:', decrypted_message)
