#include <cstring>
#include "BSPMap.hpp"

BSPMap::~BSPMap() {}

void BSPMap::unload() {
    delete[]   buf.data();
    hasInit = false;
    *m_path = NULL;
    *m_mapName = NULL;
    m_header = NULL;
    m_plane = NULL;
    m_node = NULL;
    m_leaf = NULL;
}

bool BSPMap::IsNull() {
    if (buf.data() == NULL)
        return true;

    if (*m_path == NULL)
        return true;

    if (*m_mapName == NULL)
        return true;

    if (m_header == NULL)
        return true;

    if (m_plane == NULL)
        return true;

    if (m_node == NULL)
        return true;

    if (m_leaf == NULL)
        return true;

    return false;
}

bool BSPMap::load(const char *path) {
    strcpy(m_path, path);

    std::string fPath(m_path);
    fPath += "/csgo/";
    char map[40];
    engine.GetMapName(map);
    fPath += map;
    strcpy(m_mapName, map);

    std::ifstream hFile(fPath.c_str(), std::ios::binary | std::ios::ate);
    std::streamsize size = hFile.tellg();
    hFile.seekg(0, std::ios::beg);

    if (hFile.bad())
        return false;

    buf.resize(size);
    hFile.read(buf.data(), size);

    m_header = (dheader_t *) buf.data();

    m_node = (dnode_t *) (buf.data() + m_header->lumps[LUMP_NODES].fileofs);
    m_plane = (dplane_t *) (buf.data() + m_header->lumps[LUMP_PLANES].fileofs);
    m_leaf = (dleaf_t *) (buf.data() + m_header->lumps[LUMP_LEAVES].fileofs);

    return true;
}

void BSPMap::DisplayInfo() {
}

void BSPMap::setPath(const char *path) {
    strcpy(m_path, path);
}

int BSPMap::getVersion() {
    return m_header->version;
}

int BSPMap::getRevision() {
    return m_header->mapRevision;
}

const char *BSPMap::getPath() {
    return m_path;
}

const char *BSPMap::getName() {
    return m_mapName;
}

dnode_t *BSPMap::getNodeLump() {
    return m_node;
}

dleaf_t *BSPMap::getLeafLump() {
    return m_leaf;
}

dplane_t *BSPMap::getPlaneLump() {
    return m_plane;
}

dleaf_t *BSPMap::GetLeafFromPoint(const Vector point) {
    int nodenum = 0;
    dnode_t *node;
    dplane_t *plane;

    float d = 0.0f;

    while (nodenum >= 0) {
        if (&m_node == NULL || &m_plane == NULL)
            return NULL;

        node = &m_node[nodenum];
        plane = &m_plane[node->planenum];
        d = point.Dot(plane->normal) - plane->dist;
        if (d > 0)
            nodenum = node->children[0];
        else
            nodenum = node->children[1];
    }

    return &m_leaf[-nodenum - 1];
}

bool BSPMap::Visible(const Vector &vStart, const Vector &vEnd) {
    if (IsNull()) {
        return false;
    }

    Vector direction = vEnd - vStart;
    Vector point = vStart;

    float steps = direction.Length();
    if (steps > 4000.0f)
        return false;

    direction /= steps;

    dleaf_t *leaf = nullptr;

    while (steps > 0) {
        point += direction;
        leaf = GetLeafFromPoint(point);
        if (leaf->contents & CONTENTS_SOLID || leaf->contents & CONTENTS_HITBOX) {
            return false;
        }
        --steps;
    }
    return true;
}
