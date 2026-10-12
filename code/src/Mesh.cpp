#include "Mesh.h"

// Mise à jour de la signature ici aussi
Mesh::Mesh(const std::vector<std::array<float, 3>>& V, const std::vector<std::array<int, 3>>& F) {
    std::cout << "[DEBUG] Début de la création du Mesh." << std::endl;
    std::cout << "[DEBUG] Nombre de sommets reçus : " << V.size() << std::endl;
    std::cout << "[DEBUG] Nombre de faces reçues : " << F.size() << std::endl;
    tabVertex.resize(V.size());
    for (size_t i = 0; i < V.size(); ++i) {
        Vertex* tmp = new Vertex();
        tmp->x = V[i][0]; // L'accès avec crochets marche parfaitement avec std::array
        tmp->y = V[i][1];
        tmp->z = V[i][2];
        tmp->he = nullptr;
        tabVertex[i] = tmp;
    }
    std::cout << "[DEBUG] Initialisation des sommets terminée." << std::endl;
    tabFace.resize(F.size());
    for (size_t i = 0; i < F.size(); ++i) {
        Face* tmp = new Face();
        tmp->he = nullptr;
        tabFace[i] = tmp;
    }
    std::cout << "[DEBUG] Initialisation des faces terminée." << std::endl;
    tabHE.resize(3 * F.size());
    for (size_t i = 0; i < F.size(); ++i) {
        // On soustrait 1 pour passer de la base 1 (fichier OBJ) à la base 0 (C++)
        int v0 = F[i][0] - 1;
        int v1 = F[i][1] - 1;
        int v2 = F[i][2] - 1;

        // Sécurité ultime pour éviter tout autre crash
        if (v0 < 0 || v1 < 0 || v2 < 0 || v0 >= V.size() || v1 >= V.size() || v2 >= V.size()) {
            std::cerr << "ERREUR : Indices de face hors limites pour la face " << i << std::endl;
            continue; // Passe à la face suivante sans planter
        }

        HalfEdge* pHE0 = new HalfEdge();
        HalfEdge* pHE1 = new HalfEdge();
        HalfEdge* pHE2 = new HalfEdge();

        // Renseignement des cibles (Target) avec nos nouveaux indices corrigés
        pHE0->target = tabVertex[v1];
        pHE1->target = tabVertex[v2];
        pHE2->target = tabVertex[v0];

        // Renseignement des suivants (Next)
        pHE0->next = pHE1;
        pHE1->next = pHE2;
        pHE2->next = pHE0;

        // Renseignement des faces
        pHE0->face = tabFace[i];
        pHE1->face = tabFace[i];
        pHE2->face = tabFace[i];
        
        // Renseignement des jumeaux (Twin)
        pHE0->twin = nullptr;
        pHE1->twin = nullptr;
        pHE2->twin = nullptr;

        // Liaison des sommets vers un de leurs Half-Edges
        if (tabVertex[v0]->he == nullptr) tabVertex[v0]->he = pHE0;
        if (tabVertex[v1]->he == nullptr) tabVertex[v1]->he = pHE1;
        if (tabVertex[v2]->he == nullptr) tabVertex[v2]->he = pHE2;

        // Liaison de la face vers un de ses Half-Edges
        if (tabFace[i]->he == nullptr) tabFace[i]->he = pHE0;

        tabHE[3 * i + 0] = pHE0;
        tabHE[3 * i + 1] = pHE1;
        tabHE[3 * i + 2] = pHE2;
    }
    std::cout << "[DEBUG] Initialisation des half_edge terminée." << std::endl;
}

Mesh::~Mesh() {
    for (Vertex* v : tabVertex) delete v;
    for (Face* f : tabFace) delete f;
    for (HalfEdge* he : tabHE) delete he;
}