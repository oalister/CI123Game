#include "SFApp.h"
int spawner=3;
SFApp::SFApp() : fire(0), is_running(true), pcol(true), direction(1), score(0) {

  surface = SDL_GetVideoSurface();
  app_box = make_shared<SFBoundingBox>(Vector2(surface->w/2, surface->h/2), surface->w/2, surface->h/2);
  player  = make_shared<SFAsset>(SFASSET_PLAYER);
  auto player_pos = Point2(surface->w/2, 88.0f);
  player->SetPosition(player_pos);


  const int number_of_aliens = 8;
  for(int i=0; i<number_of_aliens; i++) {
    // place an alien at width/number_of_aliens * i
    auto alien = make_shared<SFAsset>(SFASSET_ALIEN);
    auto pos   = Point2((surface->w/number_of_aliens) * i, 400.0f);
    alien->SetPosition(pos);
    aliens.push_back(alien);
  }

  const int number_of_coins = 3;
  for(int i=0; i<number_of_coins; i++) {

    auto coin = make_shared<SFAsset>(SFASSET_COIN);
    auto pos   = Point2(((surface->w/number_of_coins+1))*(i) , 460.0f);
    coin->SetPosition(pos);
    coins.push_back(coin);
  }

  const int number_of_walls = 4;
  for(int i=0; i<number_of_walls; i++) {

    auto wall = make_shared<SFAsset>(SFASSET_WALL);
    auto pos   = Point2((surface->w/(number_of_walls+1)) * (i+1), 250.0f);
    wall->SetPosition(pos);
    walls.push_back(wall);
  }


    auto wall = make_shared<SFAsset>(SFASSET_WALL);
    auto pos   = Point2(surface->w, 400.0f);
    wall->SetPosition(pos);
    walls.push_back(wall);

 
}

SFApp::~SFApp() {
}

/**
 * Handle all events that come from SDL.
 * These are timer or keyboard events.
 */
void SFApp::OnEvent(SFEvent& event) {
  SFEVENT the_event = event.GetCode();
  switch (the_event) {
  case SFEVENT_QUIT:
    is_running = false;
    break;
  case SFEVENT_UPDATE:
    OnUpdateWorld();
    OnRender();
    break;
  case SFEVENT_PLAYER_DOWN:
direction=180;    
break;
  case SFEVENT_PLAYER_UP:

    player->GoNorth();
direction=0;
    break;

  case SFEVENT_PLAYER_LEFT:
direction=270;
    break;
  case SFEVENT_PLAYER_RIGHT:
direction=90;
    break;
  case SFEVENT_FIRE:
    fire ++;
    std::stringstream sstm;
    
    FireProjectile();
    break;
  }
}

int SFApp::OnExecute() {
  // Execute the app
  SDL_Event event;
  while (SDL_WaitEvent(&event) && is_running) {
    // if this is an update event, then handle it in SFApp,
    // otherwise punt it to the SFEventDispacher.
    SFEvent sfevent((const SDL_Event) event);
    OnEvent(sfevent);
  }
}

void SFApp::OnUpdateWorld() {

//change direction based on direction

switch (direction) {
  case 180:player->GoSouth();
     break;
  case 270:player->GoWest();
break;
  case 90:player->GoEast();    
    break;
      
  case 0:player->GoNorth();
break;
}

  // Update projectile positions
  for(auto p: projectiles) {
    p->GoNorth();
    p->GoNorth();
  }

  for(auto c: coins) {
 //   c->GoNorth();
  }

 //  Update enemy positions
  for(auto a : aliens) {


a->GoEast();
}


if(pcol==true){
pcol=false;
}   
else{
pcol=true;
}

  

  // Detect collisions
  for(auto p : projectiles) {
    for(auto a : aliens) {
      if(p->CollidesWith(a)) {
        if(p->IsAlive()) {
	p->HandleCollision();
        a->HandleCollision();
}}}}

for(auto p : projectiles) {
    for(auto w : walls){
if(p->CollidesWith(w)){
        p->HandleCollision();
}}}

for(auto a : aliens) {
    for(auto w : walls){
if(a->CollidesWith(w)){
				auto pos   = Point2(0.0f,400.0f);
        a->SetPosition(pos);
}}}

    for(auto a : aliens) {
      if(a->CollidesWith(player)) {
cerr << "Game over!" << endl;
cerr << "Score: " << score << endl;
is_running = false;
	}} 

 for(auto c : coins) {
if(c->IsAlive()) {
if(player->CollidesWith(c)) {

		c->HandleCollision();
    score=score+10;
    std::stringstream sstm;
    sstm << "Score " << score;
    SDL_WM_SetCaption(sstm.str().c_str(),  sstm.str().c_str());
}
}
}

   for(auto w : walls) {
   while(w->CollidesWith(player)) {
 switch (direction) {
  case 0:player->GoSouth();
     break;
  case 90:player->GoWest();
break;
  case 270:player->GoEast();    
    break;
      
  case 180:player->GoNorth();
break;
	}}}

  

  // remove dead aliens (the long way)
  list<shared_ptr<SFAsset>> tmp;
  int comp=0;
for(auto a : aliens) {

    if(a->IsAlive()) {
      tmp.push_back(a);
comp++;
    }
  }
if (comp==0)
{
cerr << "Game Complete!" << endl;
cerr << "Score: " << score << endl;
is_running = false;
}
  aliens.clear();
  aliens = list<shared_ptr<SFAsset>>(tmp);
}

void SFApp::OnRender() {



  // clear the surface
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 8, 54, 129) );

  // draw the player
  player->OnRender(surface);

  for(auto p: projectiles) {
    if(p->IsAlive()) {p->OnRender(surface);}
  }

  for(auto a: aliens) {
    if(a->IsAlive()) {a->OnRender(surface);}
  }

  for(auto c: coins) {
   if(c->IsAlive()) {c->OnRender(surface);}
  }
for(auto w: walls) {
   if(w->IsAlive()) {w->OnRender(surface);}
  }

  // Switch the off-screen buffer to be on-screen
  SDL_Flip(surface);
}

void SFApp::FireProjectile() {
  auto pb = make_shared<SFAsset>(SFASSET_PROJECTILE);
  auto v  = player->GetPosition();
  pb->SetPosition(v);
  projectiles.push_back(pb);
}
