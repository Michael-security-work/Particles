#include "Engine.h"
#include <iostream>
#include <ctime>

Engine::Engine()
{
    srand(static_cast<unsigned int>(time(NULL)));
    m_Window.create(VideoMode::getDesktopMode(), "Particles");
}

void Engine::run()
{
    Clock clock;
    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete.  Starting engine..." << endl;

    while (m_Window.isOpen())
    {
        Time dt = clock.restart();
        float dtAsSeconds = dt.asSeconds();

        input();
        update(dtAsSeconds);
        draw();
    }
}

void Engine::input()
{
    Event event;
    while (m_Window.pollEvent(event))
    {
        if (event.type == Event::Closed) m_Window.close();
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) m_Window.close();

        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            for (int i = 0; i < 5; i++)
            {
                int numPoints = (rand() % 26) + 25;
                Vector2i mousePos = Mouse::getPosition(m_Window);
                m_particles.push_back(Particle(m_Window, numPoints, mousePos));
            }
        }
    }
}

void Engine::update(float dtAsSeconds)
{
    for (auto it = m_particles.begin(); it != m_particles.end(); )
    {
        if (it->getTTL() > 0.0)
        {
            it->update(dtAsSeconds);
            ++it;
        }
        else
        {
            it = m_particles.erase(it);
        }
    }
}

void Engine::draw()
{
    m_Window.clear();

    for (const Particle& p : m_particles)
    {
        m_Window.draw(p);
    }

    m_Window.display();
}