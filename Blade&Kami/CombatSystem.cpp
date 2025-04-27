// CombatSystem.cpp
#include "CombatSystem.h"
#include "CombatLogic.h"

CombatSystem::CombatResult CombatSystem::updateCombat(Player& player, Enemy& enemy, int playerAction) {
    // ��������� �������� ������
    CombatLogic::processPlayerAction(player, enemy, playerAction);
    if (!enemy.isAlive()) return PLAYER_WIN;

    // ��������� �������� �����
    CombatLogic::processEnemyAction(player, enemy);
    if (!player.isAlive()) return ENEMY_WIN;

    return IN_PROGRESS;
}