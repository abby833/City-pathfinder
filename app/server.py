import osmnx as ox

def normalizeaza_text(text):
    # inlocuiesc diacriticile cu varainta lor standard
    tabel = str.maketrans("ăâîșțĂÂÎȘȚ", "aaistAAIST")
    return text.translate(tabel)

def descarca_harta_si_salveaza(locatie, cale_statii, cale_coordonate, cale_nume):
    print(f"Descarc harta pentru: {locatie}...")
    
    #Descarc reteaua
    G = ox.graph_from_place(locatie, network_type='all_public')
    
    # Salvez distantzele pt codul c++ - statii.txt
    with open(cale_statii, 'w', encoding='utf-8') as f: #Ma asigur ca vor aparea si diacriticile
        for u, v, data in G.edges(data=True):
            f.write(f"{u},{v},{data.get('length', 0)}\n")
    print(f"Datele salvate în {cale_statii}")
    
    # Salvez coordonatele GPS - coordonate.txt 
    with open(cale_coordonate, 'w', encoding='utf-8') as f:
        for nod_id, data in G.nodes(data=True):
            f.write(f"{nod_id},{data['y']},{data['x']}\n")
    print(f"Coordonatele salvate în {cale_coordonate}")
    
    # Salvez dictionarul de nume (nume_strazi.txt)
    with open(cale_nume, 'w', encoding='utf-8') as f:
        for u, v, data in G.edges(data=True):
            if 'name' in data:
                nume = data['name'] if isinstance(data['name'], str) else data['name'][0]
                nume_curat = normalizeaza_text(nume) 
                f.write(f"{nume_curat},{u},{v}\n")
    print(f"Dicționarul salvat în {cale_nume}")

if __name__ == "__main__":
    descarca_harta_si_salveaza(
        locatie="Iași, Romania", 
        cale_statii="src/statii.txt",
        cale_coordonate="src/coordonate.txt",
        cale_nume="src/nume_strazi.txt"
    )