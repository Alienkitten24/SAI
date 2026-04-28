import asyncio
from bleserver import start_server

async def main():
    await start_server()

if __name__ == "__main__":
    asyncio.run(main())
