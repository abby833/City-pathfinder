import folium

def genereaza_harta_html(fisier_traseu="src/traseu.txt", fisier_coords="src/coordonate.txt"):
    # Incarc coordonatele in memorie
    coords = {}
    with open(fisier_coords, 'r') as f:
        for linie in f:
            parti = linie.strip().split(',')
            if len(parti) == 3:
                coords[parti[0]] = (float(parti[1]), float(parti[2]))
                
    # Reconstruiesc drumul lista de coordonate
    traseu_gps = []
    with open(fisier_traseu, 'r') as f:
        for linie in f:
            nod = linie.strip()
            if nod in coords:
                traseu_gps.append(coords[nod])
                
    if not traseu_gps:
        return None
        
    # Desenez harta centrala pe punctul de plecare
    m = folium.Map(location=traseu_gps[0], zoom_start=15)
    folium.PolyLine(locations=traseu_gps, color="blue", weight=5, opacity=0.8).add_to(m)
    
    # Pun un marker la Start și unul la Destinatie
    folium.Marker(traseu_gps[0], tooltip="Start", icon=folium.Icon(color="green")).add_to(m)
    folium.Marker(traseu_gps[-1], tooltip="Destinație", icon=folium.Icon(color="red")).add_to(m)
    
    m.save("harta_ruta.html")
    return "harta_ruta.html"