#pragma once
#include <vector>
#include <map>
#include "Fixed64.h"
#include "Grid.h"
#include "Constants.h"

namespace BABO::Physics {
    using namespace BABO::Math;
    using namespace BABO::World;
    using namespace BABO::Core;

    enum class PhysicsProperty {
        None = 0,
        Solid = 1 << 0,   
        Pushable = 1 << 1,
        Player = 1 << 2   
    };

    struct RigidBody {
        uint32_t entityID=0;
        Vector2Fixed position;
        Vector2Fixed velocity;
        PhysicsProperty properties;
    };

    class PhysicsSolver {
    private:
        GridSystem* m_grid;
        std::map<uint32_t, RigidBody> m_bodies;

        Fix64 GRAVITY = Fix64(0.8f);

    public:
        PhysicsSolver(GridSystem* grid) : m_grid(grid) {}

        void Clear() { m_bodies.clear(); }

        void RegisterEntity(uint32_t id, int wordId, Fix64 x, Fix64 y) {
            RigidBody body;
            body.entityID = id;
            body.position = { x, y };
            body.velocity = { Fix64::Zero(), Fix64::Zero() };


            if (wordId == 0) body.properties = PhysicsProperty::Player;
            else if (wordId == 1) body.properties = PhysicsProperty::Pushable;
            else body.properties = PhysicsProperty::Solid;

            m_bodies[id] = body;


            UpdateGridPosition(id, { x, y }, { x, y }, true);
        }

        RigidBody GetTransform(uint32_t id) const {
            if (m_bodies.count(id)) return m_bodies.at(id);
            return {};
        }

        void SetVelocity(uint32_t id, Fix64 vx, Fix64 vy) {
            if (m_bodies.count(id)) {
                if (vy != Fix64::Zero()) m_bodies[id].velocity.y = vy;
                m_bodies[id].velocity.x = vx;
            }
        }

        void Update(double dt) {
            for (auto& [id, body] : m_bodies) {

                if ((int)body.properties & (int)PhysicsProperty::Solid) continue;
                body.velocity.y = body.velocity.y + GRAVITY;

  
                if (body.velocity.x != Fix64::Zero()) {
                    Fix64 nextX = body.position.x + body.velocity.x;
                    if (TryMove(body, { nextX, body.position.y })) body.position.x = nextX;
                    else body.velocity.x = Fix64::Zero();
                }

                if (body.velocity.y != Fix64::Zero()) {
                    Fix64 nextY = body.position.y + body.velocity.y;
                    if (TryMove(body, { body.position.x, nextY })) body.position.y = nextY;
                    else body.velocity.y = Fix64::Zero();
                }
            }
        }

    private:
        bool TryMove(RigidBody& mover, Vector2Fixed targetPos) {
            GridPoint gp = m_grid->WorldToGrid(targetPos.x, targetPos.y);

            if (!m_grid->IsInBounds(gp.x, gp.y)) return false;

            Cell* cell = m_grid->GetCell(gp.x, gp.y);
            if (!cell || cell->isStaticWall) return false;

            for (uint32_t otherID : cell->entities) {
                if (otherID == mover.entityID) continue;
                RigidBody& other = m_bodies[otherID];

                if ((int)other.properties & (int)PhysicsProperty::Solid) return false;

                if ((int)other.properties & (int)PhysicsProperty::Pushable) {
                    Vector2Fixed pushDir = targetPos - mover.position;
                    Vector2Fixed pushTarget = other.position + pushDir;

                    if (TryMove(other, pushTarget)) {
                        UpdateGridPosition(other.entityID, other.position, pushTarget);
                        other.position = pushTarget;
                    }
                    else {
                        return false;
                    }
                }
            }
            UpdateGridPosition(mover.entityID, mover.position, targetPos);
            return true;
        }

        void UpdateGridPosition(uint32_t id, Vector2Fixed oldPos, Vector2Fixed newPos, bool force = false) {
            GridPoint oldGP = m_grid->WorldToGrid(oldPos.x, oldPos.y);
            GridPoint newGP = m_grid->WorldToGrid(newPos.x, newPos.y);

            if (force || !(oldGP == newGP)) {
                if (!force) {
                    Cell* oldCell = m_grid->GetCell(oldGP.x, oldGP.y);
                    if (oldCell) {
                        auto it = std::find(oldCell->entities.begin(), oldCell->entities.end(), id);
                        if (it != oldCell->entities.end()) oldCell->entities.erase(it);
                    }
                }
                Cell* newCell = m_grid->GetCell(newGP.x, newGP.y);
                if (newCell) newCell->entities.push_back(id);
            }
        }
    };
}