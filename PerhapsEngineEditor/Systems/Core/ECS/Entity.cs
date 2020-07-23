using System;

namespace Perhaps.Engine
{
    public class Entity
    {
        public uint entityId { get; private set; }

        public Entity(uint _entityId)
        {
            
            entityId = _entityId;
        }

    }
}
