#pragma once
#include <map>
#include <vector>
#include <algorithm>
#include "Fix64.h"
#include "Grid.h"

namespace BABO::Physics {
    using namespace BABO::Math;
    using namespace BABO::World;

    enum class PhysicsProperty { None = 0, Solid = 1, Pushable = 2, Player = 4 };

    struct RigidBody {
        uint32_t entityID;
        Vector2Fix position;
        Vector2Fix velocity;
        PhysicsProperty properties;
    };

    class PhysicsSolver {
        GridSystem* m_grid;
        std::map<uint32_t, RigidBody> m_bodies;
        Fix64 GRAVITY = Fix64(0.8f);

    public:
        PhysicsSolver(GridSystem* grid) : m_grid(grid) {}

        void Clear() { m_bodies.clear(); }

        void RegisterEntity(uint32_t id, int type, Fix64 x, Fix64 y) {
            RigidBody rb;
            rb.entityID = id;
            rb.position = { x, y };
            rb.velocity = { Fix64::Zero(), Fix64::Zero() };

            if (type == 0) rb.properties = PhysicsProperty::Player;
            else if (type == 1) rb.properties = PhysicsProperty::Solid;
            else rb.properties = PhysicsProperty::Pushable;

            m_bodies[id] = rb;

            GridPoint gp = m_grid->WorldToGrid(x, y);
            if (m_grid->IsInBounds(gp.x, gp.y))
                m_grid->GetCell(gp.x, gp.y)->entities.push_back(id);
        }

        RigidBody GetTransform(uint32_t id) const {
            auto it = m_bodies.find(id);
            if (it != m_bodies.end()) return it->second;
            return {};
        }

        void SetVelocity(uint32_t id, Fix64 vx, Fix64 vy) {
            auto it = m_bodies.find(id);
            if (it != m_bodies.end()) {
                if (vy.Raw() != 0) it->second.velocity.y = vy;
                it->second.velocity.x = vx;
            }
        }

        void Update() {
            for (auto& pair : m_bodies) {
                RigidBody& body = pair.second;
                if ((int)body.properties & (int)PhysicsProperty::Solid) continue;

                body.velocity.y = body.velocity.y + GRAVITY; 


                if (body.velocity.x.Raw() != 0) {
                    Fix64 nextX = body.position.x + body.velocity.x;
                    if (TryMove(body, { nextX, body.position.y })) body.position.x = nextX;
                    else body.velocity.x = Fix64::Zero();
                }
                if (body.velocity.y.Raw() != 0) {
                    Fix64 nextY = body.position.y + body.velocity.y;
                    if (TryMove(body, { body.position.x, nextY })) body.position.y = nextY;
                    else body.velocity.y = Fix64::Zero();
                }
            }
        }

    private:
        bool TryMove(RigidBody& mover, Vector2Fix targetPos) {
            GridPoint gp = m_grid->WorldToGrid(targetPos.x, targetPos.y);
            if (!m_grid->IsInBounds(gp.x, gp.y)) return false;

            Cell* cell = m_grid->GetCell(gp.x, gp.y);
            if (!cell || cell->isStaticWall) return false;

            for (uint32_t otherID : cell->entities) {
                if (otherID == mover.entityID) continue;

  
                auto it = m_bodies.find(otherID);
                if (it == m_bodies.end()) continue;
                RigidBody& other = it->second;

                if ((int)other.properties & (int)PhysicsProperty::Solid) return false;

                if ((int)other.properties & (int)PhysicsProperty::Pushable) {
                    Vector2Fix pushDir = targetPos - mover.position;
                    Vector2Fix pushTarget = other.position + pushDir;

                    if (TryMove(other, pushTarget)) {
                        UpdateGridPosition(other.entityID, other.position, pushTarget);
                        other.position = pushTarget;
                    }
                    else {
                        return false;
                    }
                }
            }
            // Update mover's grid position if move is successful
            UpdateGridPosition(mover.entityID, mover.position, targetPos);
            return true;
        }

        void UpdateGridPosition(uint32_t id, Vector2Fix oldPos, Vector2Fix newPos) {
            GridPoint oldGP = m_grid->WorldToGrid(oldPos.x, oldPos.y);
            GridPoint newGP = m_grid->WorldToGrid(newPos.x, newPos.y);
            if (oldGP.x == newGP.x && oldGP.y == newGP.y) return;

            // Remove from old cell
            if (m_grid->IsInBounds(oldGP.x, oldGP.y)) {
                Cell* oldCell = m_grid->GetCell(oldGP.x, oldGP.y);
                auto it = std::find(oldCell->entities.begin(), oldCell->entities.end(), id);
                if (it != oldCell->entities.end()) oldCell->entities.erase(it);
            }

            // Add to new cell
            if (m_grid->IsInBounds(newGP.x, newGP.y)) {
                m_grid->GetCell(newGP.x, newGP.y)->entities.push_back(id);
            }
        }
    };
}