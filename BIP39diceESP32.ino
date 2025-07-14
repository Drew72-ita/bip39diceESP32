#include <TFT_eSPI.h>
#include <SPI.h>
#include <Crypto.h>
#include <SHA256.h>

TFT_eSPI tft = TFT_eSPI();

#define BTN_NEXT    0
#define BTN_SELECT  35

const char* version = "0.1.0";

const char* WORDLIST[2048] = {
  "abandon", "ability", "able", "about", "above", "absent", "absorb", "abstract", "absurd", "abuse", "access", "accident", "account", "accuse", "achieve", "acid", "acoustic", "acquire", "across", "act", "action", "actor", "actress", "actual", "adapt", "add", "addict", "address", "adjust", "admit", "adult", "advance", "advice", "aerobic", "affair", "afford", "afraid", "again", "age", "agent", "agree", "ahead", "aim", "air", "airport", "aisle", "alarm", "album", "alcohol", "alert", "alien", "all", "alley", "allow", "almost", "alone", "alpha", "already", "also", "alter", "always", "amateur", "amazing", "among", "amount", "amused", "analyst", "anchor", "ancient", "anger", "angle", "angry", "animal", "ankle", "announce", "annual", "another", "answer", "antenna", "antique", "anxiety", "any", "apart", "apology", "appear", "apple", "approve", "april", "arch", "arctic", "area", "arena", "argue", "arm", "armed", "armor", "army", "around", "arrange", "arrest", "arrive", "arrow", "art", "artefact", "artist", "artwork", "ask", "aspect", "assault", "asset", "assist", "assume", "asthma", "athlete", "atom", "attack", "attend", "attitude", "attract", "auction", "audit", "august", "aunt", "author", "auto", "autumn", "average", "avocado", "avoid", "awake", "aware", "away", "awesome", "awful", "awkward", "axis", "baby", "bachelor", "bacon", "badge", "bag", "balance", "balcony", "ball", "bamboo", "banana", "banner", "bar", "barely", "bargain", "barrel", "base", "basic", "basket", "battle", "beach", "bean", "beauty", "because", "become", "beef", "before", "begin", "behave", "behind", "believe", "below", "belt", "bench", "benefit", "best", "betray", "better", "between", "beyond", "bicycle", "bid", "bike", "bind", "biology", "bird", "birth", "bitter", "black", "blade", "blame", "blanket", "blast", "bleak", "bless", "blind", "blood", "blossom", "blouse", "blue", "blur", "blush", "board", "boat", "body", "boil", "bomb", "bone", "bonus", "book", "boost", "border", "boring", "borrow", "boss", "bottom", "bounce", "box", "boy", "bracket", "brain", "brand", "brass", "brave", "bread", "breeze", "brick", "bridge", "brief", "bright", "bring", "brisk", "broccoli", "broken", "bronze", "broom", "brother", "brown", "brush", "bubble", "buddy", "budget", "buffalo", "build", "bulb", "bulk", "bullet", "bundle", "bunker", "burden", "burger", "burst", "bus", "business", "busy", "butter", "buyer", "buzz", "cabbage", "cabin", "cable", "cactus", "cage", "cake", "call", "calm", "camera", "camp", "can", "canal", "cancel", "candy", "cannon", "canoe", "canvas", "canyon", "capable", "capital", "captain", "car", "carbon", "card", "cargo", "carpet", "carry", "cart", "case", "cash", "casino", "castle", "casual", "cat", "catalog", "catch", "category", "cattle", "caught", "cause", "caution", "cave", "ceiling", "celery", "cement", "census", "century", "cereal", "certain", "chair", "chalk", "champion", "change", "chaos", "chapter", "charge", "chase", "chat", "cheap", "check", "cheese", "chef", "cherry", "chest", "chicken", "chief", "child", "chimney", "choice", "choose", "chronic", "chuckle", "chunk", "churn", "cigar", "cinnamon", "circle", "citizen", "city", "civil", "claim", "clap", "clarify", "claw", "clay", "clean", "clerk", "clever", "click", "client", "cliff", "climb", "clinic", "clip", "clock", "clog", "close", "cloth", "cloud", "clown", "club", "clump", "cluster", "clutch", "coach", "coast", "coconut", "code", "coffee", "coil", "coin", "collect", "color", "column", "combine", "come", "comfort", "comic", "common", "company", "concert", "conduct", "confirm", "congress", "connect", "consider", "control", "convince", "cook", "cool", "copper", "copy", "coral", "core", "corn", "correct", "cost", "cotton", "couch", "country", "couple", "course", "cousin", "cover", "coyote", "crack", "cradle", "craft", "cram", "crane", "crash", "crater", "crawl", "crazy", "cream", "credit", "creek", "crew", "cricket", "crime", "crisp", "critic", "crop", "cross", "crouch", "crowd", "crucial", "cruel", "cruise", "crumble", "crunch", "crush", "cry", "crystal", "cube", "culture", "cup", "cupboard", "curious", "current", "curtain", "curve", "cushion", "custom", "cute", "cycle", "dad", "damage", "damp", "dance", "danger", "daring", "dash", "daughter", "dawn", "day", "deal", "debate", "debris", "decade", "december", "decide", "decline", "decorate", "decrease", "deer", "defense", "define", "defy", "degree", "delay", "deliver", "demand", "demise", "denial", "dentist", "deny", "depart", "depend", "deposit", "depth", "deputy", "derive", "describe", "desert", "design", "desk", "despair", "destroy", "detail", "detect", "develop", "device", "devote", "diagram", "dial", "diamond", "diary", "dice", "diesel", "diet", "differ", "digital", "dignity", "dilemma", "dinner", "dinosaur", "direct", "dirt", "disagree", "discover", "disease", "dish", "dismiss", "disorder", "display", "distance", "divert", "divide", "divorce", "dizzy", "doctor", "document", "dog", "doll", "dolphin", "domain", "donate", "donkey", "donor", "door", "dose", "double", "dove", "draft", "dragon", "drama", "drastic", "draw", "dream", "dress", "drift", "drill", "drink", "drip", "drive", "drop", "drum", "dry", "duck", "dumb", "dune", "during", "dust", "dutch", "duty", "dwarf", "dynamic", "eager", "eagle", "early", "earn", "earth", "easily", "east", "easy", "echo", "ecology", "economy", "edge", "edit", "educate", "effort", "egg", "eight", "either", "elbow", "elder", "electric", "elegant", "element", "elephant", "elevator", "elite", "else", "embark", "embody", "embrace", "emerge", "emotion", "employ", "empower", "empty", "enable", "enact", "end", "endless", "endorse", "enemy", "energy", "enforce", "engage", "engine", "enhance", "enjoy", "enlist", "enough", "enrich", "enroll", "ensure", "enter", "entire", "entry", "envelope", "episode", "equal", "equip", "era", "erase", "erode", "erosion", "error", "erupt", "escape", "essay", "essence", "estate", "eternal", "ethics", "evidence", "evil", "evoke", "evolve", "exact", "example", "excess", "exchange", "excite", "exclude", "excuse", "execute", "exercise", "exhaust", "exhibit", "exile", "exist", "exit", "exotic", "expand", "expect", "expire", "explain", "expose", "express", "extend", "extra", "eye", "eyebrow", "fabric", "face", "faculty", "fade", "faint", "faith", "fall", "false", "fame", "family", "famous", "fan", "fancy", "fantasy", "farm", "fashion", "fat", "fatal", "father", "fatigue", "fault", "favorite", "feature", "february", "federal", "fee", "feed", "feel", "female", "fence", "festival", "fetch", "fever", "few", "fiber", "fiction", "field", "figure", "file", "film", "filter", "final", "find", "fine", "finger", "finish", "fire", "firm", "first", "fiscal", "fish", "fit", "fitness", "fix", "flag", "flame", "flash", "flat", "flavor", "flee", "flight", "flip", "float", "flock", "floor", "flower", "fluid", "flush", "fly", "foam", "focus", "fog", "foil", "fold", "follow", "food", "foot", "force", "forest", "forget", "fork", "fortune", "forum", "forward", "fossil", "foster", "found", "fox", "fragile", "frame", "frequent", "fresh", "friend", "fringe", "frog", "front", "frost", "frown", "frozen", "fruit", "fuel", "fun", "funny", "furnace", "fury", "future", "gadget", "gain", "galaxy", "gallery", "game", "gap", "garage", "garbage", "garden", "garlic", "garment", "gas", "gasp", "gate", "gather", "gauge", "gaze", "general", "genius", "genre", "gentle", "genuine", "gesture", "ghost", "giant", "gift", "giggle", "ginger", "giraffe", "girl", "give", "glad", "glance", "glare", "glass", "glide", "glimpse", "globe", "gloom", "glory", "glove", "glow", "glue", "goat", "goddess", "gold", "good", "goose", "gorilla", "gospel", "gossip", "govern", "gown", "grab", "grace", "grain", "grant", "grape", "grass", "gravity", "great", "green", "grid", "grief", "grit", "grocery", "group", "grow", "grunt", "guard", "guess", "guide", "guilt", "guitar", "gun", "gym", "habit", "hair", "half", "hammer", "hamster", "hand", "happy", "harbor", "hard", "harsh", "harvest", "hat", "have", "hawk", "hazard", "head", "health", "heart", "heavy", "hedgehog", "height", "hello", "helmet", "help", "hen", "hero", "hidden", "high", "hill", "hint", "hip", "hire", "history", "hobby", "hockey", "hold", "hole", "holiday", "hollow", "home", "honey", "hood", "hope", "horn", "horror", "horse", "hospital", "host", "hotel", "hour", "hover", "hub", "huge", "human", "humble", "humor", "hundred", "hungry", "hunt", "hurdle", "hurry", "hurt", "husband", "hybrid", "ice", "icon", "idea", "identify", "idle", "ignore", "ill", "illegal", "illness", "image", "imitate", "immense", "immune", "impact", "impose", "improve", "impulse", "inch", "include", "income", "increase", "index", "indicate", "indoor", "industry", "infant", "inflict", "inform", "inhale", "inherit", "initial", "inject", "injury", "inmate", "inner", "innocent", "input", "inquiry", "insane", "insect", "inside", "inspire", "install", "intact", "interest", "into", "invest", "invite", "involve", "iron", "island", "isolate", "issue", "item", "ivory", "jacket", "jaguar", "jar", "jazz", "jealous", "jeans", "jelly", "jewel", "job", "join", "joke", "journey", "joy", "judge", "juice", "jump", "jungle", "junior", "junk", "just", "kangaroo", "keen", "keep", "ketchup", "key", "kick", "kid", "kidney", "kind", "kingdom", "kiss", "kit", "kitchen", "kite", "kitten", "kiwi", "knee", "knife", "knock", "know", "lab", "label", "labor", "ladder", "lady", "lake", "lamp", "language", "laptop", "large", "later", "latin", "laugh", "laundry", "lava", "law", "lawn", "lawsuit", "layer", "lazy", "leader", "leaf", "learn", "leave", "lecture", "left", "leg", "legal", "legend", "leisure", "lemon", "lend", "length", "lens", "leopard", "lesson", "letter", "level", "liar", "liberty", "library", "license", "life", "lift", "light", "like", "limb", "limit", "link", "lion", "liquid", "list", "little", "live", "lizard", "load", "loan", "lobster", "local", "lock", "logic", "lonely", "long", "loop", "lottery", "loud", "lounge", "love", "loyal", "lucky", "luggage", "lumber", "lunar", "lunch", "luxury", "lyrics", "machine", "mad", "magic", "magnet", "maid", "mail", "main", "major", "make", "mammal", "man", "manage", "mandate", "mango", "mansion", "manual", "maple", "marble", "march", "margin", "marine", "market", "marriage", "mask", "mass", "master", "match", "material", "math", "matrix", "matter", "maximum", "maze", "meadow", "mean", "measure", "meat", "mechanic", "medal", "media", "melody", "melt", "member", "memory", "mention", "menu", "mercy", "merge", "merit", "merry", "mesh", "message", "metal", "method", "middle", "midnight", "milk", "million", "mimic", "mind", "minimum", "minor", "minute", "miracle", "mirror", "misery", "miss", "mistake", "mix", "mixed", "mixture", "mobile", "model", "modify", "mom", "moment", "monitor", "monkey", "monster", "month", "moon", "moral", "more", "morning", "mosquito", "mother", "motion", "motor", "mountain", "mouse", "move", "movie", "much", "muffin", "mule", "multiply", "muscle", "museum", "mushroom", "music", "must", "mutual", "myself", "mystery", "myth", "naive", "name", "napkin", "narrow", "nasty", "nation", "nature", "near", "neck", "need", "negative", "neglect", "neither", "nephew", "nerve", "nest", "net", "network", "neutral", "never", "news", "next", "nice", "night", "noble", "noise", "nominee", "noodle", "normal", "north", "nose", "notable", "note", "nothing", "notice", "novel", "now", "nuclear", "number", "nurse", "nut", "oak", "obey", "object", "oblige", "obscure", "observe", "obtain", "obvious", "occur", "ocean", "october", "odor", "off", "offer", "office", "often", "oil", "okay", "old", "olive", "olympic", "omit", "once", "one", "onion", "online", "only", "open", "opera", "opinion", "oppose", "option", "orange", "orbit", "orchard", "order", "ordinary", "organ", "orient", "original", "orphan", "ostrich", "other", "outdoor", "outer", "output", "outside", "oval", "oven", "over", "own", "owner", "oxygen", "oyster", "ozone", "pact", "paddle", "page", "pair", "palace", "palm", "panda", "panel", "panic", "panther", "paper", "parade", "parent", "park", "parrot", "party", "pass", "patch", "path", "patient", "patrol", "pattern", "pause", "pave", "payment", "peace", "peanut", "pear", "peasant", "pelican", "pen", "penalty", "pencil", "people", "pepper", "perfect", "permit", "person", "pet", "phone", "photo", "phrase", "physical", "piano", "picnic", "picture", "piece", "pig", "pigeon", "pill", "pilot", "pink", "pioneer", "pipe", "pistol", "pitch", "pizza", "place", "planet", "plastic", "plate", "play", "please", "pledge", "pluck", "plug", "plunge", "poem", "poet", "point", "polar", "pole", "police", "pond", "pony", "pool", "popular", "portion", "position", "possible", "post", "potato", "pottery", "poverty", "powder", "power", "practice", "praise", "predict", "prefer", "prepare", "present", "pretty", "prevent", "price", "pride", "primary", "print", "priority", "prison", "private", "prize", "problem", "process", "produce", "profit", "program", "project", "promote", "proof", "property", "prosper", "protect", "proud", "provide", "public", "pudding", "pull", "pulp", "pulse", "pumpkin", "punch", "pupil", "puppy", "purchase", "purity", "purpose", "purse", "push", "put", "puzzle", "pyramid", "quality", "quantum", "quarter", "question", "quick", "quit", "quiz", "quote", "rabbit", "raccoon", "race", "rack", "radar", "radio", "rail", "rain", "raise", "rally", "ramp", "ranch", "random", "range", "rapid", "rare", "rate", "rather", "raven", "raw", "razor", "ready", "real", "reason", "rebel", "rebuild", "recall", "receive", "recipe", "record", "recycle", "reduce", "reflect", "reform", "refuse", "region", "regret", "regular", "reject", "relax", "release", "relief", "rely", "remain", "remember", "remind", "remove", "render", "renew", "rent", "reopen", "repair", "repeat", "replace", "report", "require", "rescue", "resemble", "resist", "resource", "response", "result", "retire", "retreat", "return", "reunion", "reveal", "review", "reward", "rhythm", "rib", "ribbon", "rice", "rich", "ride", "ridge", "rifle", "right", "rigid", "ring", "riot", "ripple", "risk", "ritual", "rival", "river", "road", "roast", "robot", "robust", "rocket", "romance", "roof", "rookie", "room", "rose", "rotate", "rough", "round", "route", "royal", "rubber", "rude", "rug", "rule", "run", "runway", "rural", "sad", "saddle", "sadness", "safe", "sail", "salad", "salmon", "salon", "salt", "salute", "same", "sample", "sand", "satisfy", "satoshi", "sauce", "sausage", "save", "say", "scale", "scan", "scare", "scatter", "scene", "scheme", "school", "science", "scissors", "scorpion", "scout", "scrap", "screen", "script", "scrub", "sea", "search", "season", "seat", "second", "secret", "section", "security", "seed", "seek", "segment", "select", "sell", "seminar", "senior", "sense", "sentence", "series", "service", "session", "settle", "setup", "seven", "shadow", "shaft", "shallow", "share", "shed", "shell", "sheriff", "shield", "shift", "shine", "ship", "shiver", "shock", "shoe", "shoot", "shop", "short", "shoulder", "shove", "shrimp", "shrug", "shuffle", "shy", "sibling", "sick", "side", "siege", "sight", "sign", "silent", "silk", "silly", "silver", "similar", "simple", "since", "sing", "siren", "sister", "situate", "six", "size", "skate", "sketch", "ski", "skill", "skin", "skirt", "skull", "slab", "slam", "sleep", "slender", "slice", "slide", "slight", "slim", "slogan", "slot", "slow", "slush", "small", "smart", "smile", "smoke", "smooth", "snack", "snake", "snap", "sniff", "snow", "soap", "soccer", "social", "sock", "soda", "soft", "solar", "soldier", "solid", "solution", "solve", "someone", "song", "soon", "sorry", "sort", "soul", "sound", "soup", "source", "south", "space", "spare", "spatial", "spawn", "speak", "special", "speed", "spell", "spend", "sphere", "spice", "spider", "spike", "spin", "spirit", "split", "spoil", "sponsor", "spoon", "sport", "spot", "spray", "spread", "spring", "spy", "square", "squeeze", "squirrel", "stable", "stadium", "staff", "stage", "stairs", "stamp", "stand", "start", "state", "stay", "steak", "steel", "stem", "step", "stereo", "stick", "still", "sting", "stock", "stomach", "stone", "stool", "story", "stove", "strategy", "street", "strike", "strong", "struggle", "student", "stuff", "stumble", "style", "subject", "submit", "subway", "success", "such", "sudden", "suffer", "sugar", "suggest", "suit", "summer", "sun", "sunny", "sunset", "super", "supply", "supreme", "sure", "surface", "surge", "surprise", "surround", "survey", "suspect", "sustain", "swallow", "swamp", "swap", "swarm", "swear", "sweet", "swift", "swim", "swing", "switch", "sword", "symbol", "symptom", "syrup", "system", "table", "tackle", "tag", "tail", "talent", "talk", "tank", "tape", "target", "task", "taste", "tattoo", "taxi", "teach", "team", "tell", "ten", "tenant", "tennis", "tent", "term", "test", "text", "thank", "that", "theme", "then", "theory", "there", "they", "thing", "this", "thought", "three", "thrive", "throw", "thumb", "thunder", "ticket", "tide", "tiger", "tilt", "timber", "time", "tiny", "tip", "tired", "tissue", "title", "toast", "tobacco", "today", "toddler", "toe", "together", "toilet", "token", "tomato", "tomorrow", "tone", "tongue", "tonight", "tool", "tooth", "top", "topic", "topple", "torch", "tornado", "tortoise", "toss", "total", "tourist", "toward", "tower", "town", "toy", "track", "trade", "traffic", "tragic", "train", "transfer", "trap", "trash", "travel", "tray", "treat", "tree", "trend", "trial", "tribe", "trick", "trigger", "trim", "trip", "trophy", "trouble", "truck", "true", "truly", "trumpet", "trust", "truth", "try", "tube", "tuition", "tumble", "tuna", "tunnel", "turkey", "turn", "turtle", "twelve", "twenty", "twice", "twin", "twist", "two", "type", "typical", "ugly", "umbrella", "unable", "unaware", "uncle", "uncover", "under", "undo", "unfair", "unfold", "unhappy", "uniform", "unique", "unit", "universe", "unknown", "unlock", "until", "unusual", "unveil", "update", "upgrade", "uphold", "upon", "upper", "upset", "urban", "urge", "usage", "use", "used", "useful", "useless", "usual", "utility", "vacant", "vacuum", "vague", "valid", "valley", "valve", "van", "vanish", "vapor", "various", "vast", "vault", "vehicle", "velvet", "vendor", "venture", "venue", "verb", "verify", "version", "very", "vessel", "veteran", "viable", "vibrant", "vicious", "victory", "video", "view", "village", "vintage", "violin", "virtual", "virus", "visa", "visit", "visual", "vital", "vivid", "vocal", "voice", "void", "volcano", "volume", "vote", "voyage", "wage", "wagon", "wait", "walk", "wall", "walnut", "want", "warfare", "warm", "warrior", "wash", "wasp", "waste", "water", "wave", "way", "wealth", "weapon", "wear", "weasel", "weather", "web", "wedding", "weekend", "weird", "welcome", "west", "wet", "whale", "what", "wheat", "wheel", "when", "where", "whip", "whisper", "wide", "width", "wife", "wild", "will", "win", "window", "wine", "wing", "wink", "winner", "winter", "wire", "wisdom", "wise", "wish", "witness", "wolf", "woman", "wonder", "wood", "wool", "word", "work", "world", "worry", "worth", "wrap", "wreck", "wrestle", "wrist", "write", "wrong", "yard", "year", "yellow", "you", "young", "youth", "zebra", "zero", "zone", "zoo"
};

int step = -3;
int val_d8 = 1;
int val_hex1 = 0;
int val_hex2 = 0;
int entropy = 0;

bool haveDF = true; // true: use hexadecimal dices instead of D16 dices
int totWords = 12; // 12 or 24 words mnemonic
bool isFirstInit = true; //used for run time initialization of starting position of first throw
int intWordArray [24] = {0}; // array containing the decimal value of the words, index from 0 to 11 or 23
int nWord = 0; // word array index (from 0 to 11 / 23)
bool togglePage = true; // used to toggle between page 1 and 2 to display mnemonic in case of 24 words

//Per i dadi hex: valori da 1 a 15 + X
const char* hex_labels[17] = { "0","1","2","3","4","5","6","7","8","9",  "A", "B", "C", "D", "E", "F","X"}; 
const char* d16_labels[17] = { "1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","X"}; 

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  pinMode(BTN_NEXT, INPUT_PULLUP);
  pinMode(BTN_SELECT, INPUT_PULLUP);
  entropy = analogRead(34) ^ analogRead(39);
  randomSeed(entropy);
  drawAll();
}

/////////////////// MAIN LOOP BEGINS

void loop() {
  
  if (digitalRead(BTN_NEXT) == LOW) {
    handleNext();
    drawAll();
    delay(200);
  }

  if (digitalRead(BTN_SELECT) == LOW) {
    handleSelect();
    drawAll();
    delay(200);
  }
}
/////////////////// MAIN LOOP ENDS

/////////////////// BUTTONS HANDLERS BEGIN
void handleNext() {
  if (step == 0) {
    val_d8 = val_d8 + 1;      if (val_d8==9) { val_d8=1; }
  } else if (step == 1) {
    val_hex1 = val_hex1 + 1;  if (val_hex1==17) { val_hex1=0; }
  } else if (step == 2) {
    val_hex2 = val_hex2 + 1;  if (val_hex2==17) { val_hex2=0; }
  } else if (step == 3) {
    resetState();
  } else if (step == 4) {
    if (totWords == 24) togglePage = !togglePage;
  } else if (step == -2) {
    if (totWords == 12) totWords = 24;
    else                totWords = 12;
  } else if (step == -1) {
    haveDF = !haveDF;
  } else if (step == -3) {
    step = -2;
  }

}
 
void handleSelect() {
  if (step == 0) {
    step = 1;
  } else if (step == 1) {
    if (val_hex1 == 16) step = 0;  // X
    else step = 2;
  } else if (step == 2) {
    if (val_hex2 == 16) step = 1;  // X
    else step = 3;
  } else if (step == 3) {
    resetState();
  } else if (step == 4) {
    if (totWords == 24) togglePage = !togglePage;
  } else if (step == -2) {
    step = -1;
  } else if (step == -1) {
    step = 0;
  } else if (step == -3) {
    step = -2;
  }

}
/////////////////// BUTTONS HANDLERS END

void resetState() {
  step = 0;
  val_d8 =   random(1,  9); // random starting position for first dice
  val_hex1 = random(0, 16); // random starting position for second dice
  val_hex2 = random(0, 16); // random starting position for third dice
}

/////////////////// DRAW SCREEN BEGINS
void drawAll() {
  tft.fillScreen(TFT_BLACK);
  
  //run only once (first throw)
  if (isFirstInit) {
    val_d8 =   random(1,  9); // random starting position for first dice
    val_hex1 = random(0, 16); // random starting position for second dice
    val_hex2 = random(0, 16); // random starting position for third dice
    isFirstInit=false;
  }

  if (step ==-3) {
    tft.fillRect(0, 0, 240, 135, TFT_DARKGREY);
    drawD8 ( 40, 30, 40,       "B", 2, true, TFT_WHITE,  TFT_BLACK);
    drawDF ( 80, 30, 40,       "I", 2, true, TFT_WHITE,  TFT_BLACK);
    drawD16(120, 30, 40,       "P", 2, true, TFT_WHITE,  TFT_BLACK);
    drawD8 (160, 30, 40,       "3", 2, true, TFT_WHITE,  TFT_BLACK);
    drawDF (200, 30, 40,       "9", 2, true, TFT_WHITE,  TFT_BLACK);
    drawD8 ( 60, 70, 40,       "D", 2, true, TFT_ORANGE, TFT_WHITE);
    drawDF (100, 70, 40,       "I", 2, true, TFT_ORANGE, TFT_WHITE);
    drawD16(140, 70, 40,       "C", 2, true, TFT_ORANGE, TFT_WHITE);
    drawD8 (180, 70, 40,       "E", 2, true, TFT_ORANGE, TFT_WHITE);
    tft.setTextColor(TFT_WHITE, TFT_DARKGREY); 
    tft.setTextSize(2);
    String line1 = "v." + String(version) + " by drew72";
    int16_t x1 = (240 - tft.textWidth(line1)) / 2;
    tft.setCursor(x1, 95);
    tft.print(line1);
    tft.setTextSize(1);
    String line2 = "any button to start";
    int16_t x2 = (240 - tft.textWidth(line2)) / 2;
    tft.setCursor(x2, 120);
    tft.print(line2);
  }

  
  if (step ==-2) {
    tft.setRotation(1);       
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(1); tft.setTextDatum(TR_DATUM); 
    tft.drawString("SELECT", 235, 0, 1);   
    tft.drawString("NEXT", 235, 120, 1); 
    tft.setTextSize(3); tft.setTextDatum(TL_DATUM); 
    tft.setCursor(20, 20); tft.print("12 words");
    tft.setCursor(20, 85); tft.print("24 words");
    if (totWords==12) tft.drawRect(0, 0, 190, 65, TFT_GREEN);
    if (totWords==24) tft.drawRect(0, 65, 190, 65, TFT_GREEN);
  }

  if (step ==-1) {
    tft.setRotation(1);       
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(1); tft.setTextDatum(TR_DATUM); 
    tft.drawString("SELECT", 235, 0, 1);   
    tft.drawString("NEXT", 235, 120, 1); 
    tft.setTextSize(2); tft.setTextDatum(TL_DATUM); 
    tft.setCursor(10,  15); tft.print("one 8-sided +");
    tft.setCursor(10,  30); tft.print("two exadecimal");
    tft.setCursor(10,  85); tft.print("one 8-sided +");
    tft.setCursor(10, 100); tft.print("two 16-sided");
    if (haveDF) tft.drawRect(0,  0, 190, 65, TFT_GREEN);
    else        tft.drawRect(0, 65, 190, 65, TFT_GREEN);
  }

  if (step >= 0 && step <= 3) {

    tft.fillRect(0, 0, 240, 95, TFT_DARKGREY);
    drawD8( 40, 46, 80,       String(val_d8), 3, step >= 0, TFT_RED, TFT_BLACK);
    if (haveDF) {
      drawDF(120, 46, 80, hexLabel(val_hex1), 3, step >= 1, TFT_WHITE, TFT_BLACK);
      drawDF(200, 46, 80, hexLabel(val_hex2), 3, step >= 2, TFT_BLACK, TFT_WHITE);
    }
    else {
      drawD16(120, 46, 80, hexLabel(val_hex1), 3, step >= 1, TFT_WHITE, TFT_BLACK);
      drawD16(200, 46, 80, hexLabel(val_hex2), 3, step >= 2, TFT_BLACK, TFT_WHITE);
    }
    
    if (step==0) { tft.drawRect(  0, 5, 80, 80, TFT_GREEN); }
    if (step==1) { tft.drawRect( 80, 5, 80, 80, TFT_GREEN); }
    if (step==2) { tft.drawRect(160, 5, 80, 80, TFT_GREEN); }
    
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(2, 110);
    tft.print(String(nWord + 1) + "/" + String(totWords));
    if (nWord == totWords -1) {
      tft.setTextSize(1);
      tft.setCursor(65, 114);
      tft.print("will be adjusted for checksum");
    }

    if (step == 3) {
      int decWord = (val_d8 - 1) * 256 + (val_hex1 << 4) + val_hex2;
      intWordArray[nWord] = decWord;

      // BEGIN checksum adjustment if this is the lastword /////////////////////////////////////////////////////////////////
      if (nWord == totWords -1) {
        if (totWords == 12) {
          String bits = "";
          for (int i = 0; i < 11; i++) {
            for (int b = 10; b >= 0; b--) {
              bits += (intWordArray[i] >> b) & 1 ? '1' : '0';
            }
          }
          for (int b = 10; b >= 4; b--) { bits += (intWordArray[11] >> b) & 1 ? '1' : '0'; }
          uint8_t data[16] = {0};
          for (int i = 0; i < 128; i++) {
            int byteIndex = i / 8; int bitIndex = 7 - (i % 8);
            if (bits[i] == '1') data[byteIndex] |= (1 << bitIndex);
          }
          SHA256 hasher; hasher.reset(); hasher.update(data, 16); uint8_t hash[32];
          hasher.finalize(hash, sizeof(hash));
          uint8_t checksumBits = (hash[0] >> 4) & 0x0F;
          uint16_t prefix7 = intWordArray[11] >> 4;  
          uint16_t finalWord = (prefix7 << 4) | checksumBits;
          intWordArray[11] = finalWord;
        }
        if (totWords==24) {
          String bits = "";
          for (int i = 0; i < 23; i++) {
            for (int b = 10; b >= 0; b--) {
              bits += (intWordArray[i] >> b) & 1 ? '1' : '0';
            }
          }
          for (int b = 10; b >= 8; b--) { bits += (intWordArray[23] >> b) & 1 ? '1' : '0'; }
          uint8_t data[32] = {0};
          for (int i = 0; i < 256; i++) {
            int byteIndex = i / 8; int bitIndex = 7 - (i % 8);
            if (bits[i] == '1') data[byteIndex] |= (1 << bitIndex);
          }
          SHA256 hasher; hasher.reset(); hasher.update(data, 32); uint8_t hash[32];
          hasher.finalize(hash, sizeof(hash));
          uint8_t checksumByte = hash[0];
          uint16_t prefix3 = intWordArray[23] >> 8;
          uint16_t finalWord = (prefix3 << 8) | checksumByte;
          intWordArray[23] = finalWord;
        }
      }
      // END checksum adjustment if this is the lastword ////////////////////////////////////////////////////////////////////

      tft.setCursor(80, 110);
      tft.printf("%d=", decWord);
      tft.setCursor(140, 110);
      tft.print(WORDLIST[decWord]);
      nWord = nWord + 1 ;
      if (nWord == totWords) { step = 4; }
    }

  }
  
  if (step == 4) {
      tft.fillScreen(TFT_BLACK);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);

      int offset = 0;
      if (!togglePage) offset=12;

      for (int num = 0; num < 6; num++) {
        tft.setCursor(2, num * 18 + 2);
        tft.setTextSize(1);
        if (num + 1 + offset < 10) tft.print(" ");
        tft.print(num + 1 + offset);
        tft.setTextSize(2);
        tft.print(WORDLIST[intWordArray[num + offset]]);
        int idx = num + 6 + offset;
        tft.setCursor(122, num * 18 + 2);
        tft.setTextSize(1);
        if (idx + 1 < 10) tft.print(" ");
        tft.print(idx + 1);
        tft.setTextSize(2);
        tft.print(WORDLIST[intWordArray[idx]]);
      }

      tft.drawRect(  0,  0, 120, 110, TFT_GREEN);
      tft.drawRect(120,  0, 120, 110, TFT_GREEN);
      tft.drawRect( 0, 110, 240, 25, TFT_GREEN);
      
      if (totWords==12){
        tft.setTextSize(2); tft.setCursor(5,114);
        tft.print ("->Reset when done<-");
      }
      else {
        tft.setTextSize(1); tft.setCursor(10,120);
        tft.print ("Press for next/prev, reset when done");
      }

  }

}
/////////////////// DRAW SCREEN ENDS

String hexLabel(int val) {
  if (haveDF) { return String(hex_labels[val]); }
  else        { return String(d16_labels[val]); }
}

void drawD8(int cx, int cy, int size, String label, int sizeLabel, bool visible, uint16_t fillColor, uint16_t lineColor) {
  if (!visible) return;

  int l1 = size * 0.5; 
  int l2 = l1 * 0.91;

  int x0 = cx;               int y0 = cy - l1;
  int x1 = cx - l1 * 0.866;  int y1 = cy + l1 / 2;
  int x2 = cx + l1 * 0.866;  int y2 = cy + l1 / 2;
  int x3 = cx - l2 * 0.866;  int y3 = cy - l2 / 2;
  int x4 = cx + l2 * 0.866;  int y4 = cy - l2 / 2;
  int x5 = cx;               int y5 = cy + l2;

  tft.fillTriangle(x0, y0, x1, y1, x2, y2, fillColor); tft.drawTriangle(x0, y0, x1, y1, x2, y2, lineColor);
  tft.fillTriangle(x0, y0, x1, y1, x3, y3, fillColor); tft.drawTriangle(x0, y0, x1, y1, x3, y3, lineColor);
  tft.fillTriangle(x0, y0, x2, y2, x4, y4, fillColor); tft.drawTriangle(x0, y0, x2, y2, x4, y4, lineColor);
  tft.fillTriangle(x1, y1, x2, y2, x5, y5, fillColor); tft.drawTriangle(x1, y1, x2, y2, x5, y5, lineColor);

  tft.setTextSize(sizeLabel);
  tft.setTextColor(fillColor == TFT_BLACK ? TFT_WHITE : TFT_BLACK);
  int text_w = tft.textWidth(label);
  tft.setCursor(cx - text_w / 2, cy - 8);
  tft.print(label);
  tft.setTextSize(2);
}

void drawDF(int cx, int cy, int size, String label, int sizeLabel, bool visible, uint16_t fillColor, uint16_t lineColor) {
  if (!visible) return;

  int l = size * 0.5;

  int x0 = cx + 0.00 * l; int y0 = cy - 1.00 * l; 
  int x1 = cx - 0.58 * l; int y1 = cy + 0.50 * l;
  int x2 = cx + 0.58 * l; int y2 = cy + 0.50 * l;
  int x3 = cx - 0.90 * l; int y3 = cy - 0.27 * l;
  int x4 = cx + 0.90 * l; int y4 = cy - 0.27 * l;
  int x5 = cx - 0.90 * l; int y5 = cy + 0.18 * l;
  int x6 = cx + 0.90 * l; int y6 = cy + 0.18 * l;
  int x7 = cx + 0.00 * l; int y7 = cy + 0.91 * l; 

  tft.fillTriangle(x0, y0, x1, y1, x2, y2, fillColor); tft.drawTriangle(x0, y0, x1, y1, x2, y2, lineColor);
  tft.fillTriangle(x0, y0, x1, y1, x5, y5, fillColor); tft.drawTriangle(x0, y0, x1, y1, x5, y5, lineColor);
  tft.fillTriangle(x0, y0, x2, y2, x6, y6, fillColor); tft.drawTriangle(x0, y0, x2, y2, x6, y6, lineColor);
  tft.fillTriangle(x0, y0, x5, y5, x3, y3, fillColor); tft.drawTriangle(x0, y0, x5, y5, x3, y3, lineColor);
  tft.fillTriangle(x0, y0, x6, y6, x4, y4, fillColor); tft.drawTriangle(x0, y0, x6, y6, x4, y4, lineColor);
  tft.fillTriangle(x1, y1, x2, y2, x7, y7, fillColor); tft.drawTriangle(x1, y1, x2, y2, x7, y7, lineColor);

  tft.setTextSize(sizeLabel);
  tft.setTextColor(fillColor == TFT_BLACK ? TFT_WHITE : TFT_BLACK);
  int text_w = tft.textWidth(label);
  tft.setCursor(cx - text_w / 2, cy - 8);
  tft.print(label);
  tft.setTextSize(2);
}

void drawD16(int cx, int cy, int size, String label, int sizeLabel, bool visible, uint16_t fillColor, uint16_t lineColor) {
  if (!visible) return;

  int l = size * 0.5;

  int x0 = cx + 0.000 * l; int y0 = cy - 1.000 * l; 
  int x1 = cx + 0.866 * l; int y1 = cy - 0.500 * l;
  int x2 = cx + 0.866 * l; int y2 = cy + 0.500 * l;
  int x3 = cx + 0.000 * l; int y3 = cy + 1.000 * l;
  int x4 = cx - 0.866 * l; int y4 = cy + 0.500 * l;
  int x5 = cx - 0.866 * l; int y5 = cy - 0.500 * l;
  int x6 = cx - 0.650 * l; int y6 = cy + 0.000 * l;
  int x7 = cx + 0.650 * l; int y7 = cy + 0.000 * l;
  int x8 = cx - 0.866 * l; int y8 = cy + 0.000 * l;
  int x9 = cx + 0.866 * l; int y9 = cy + 0.000 * l;

  tft.fillTriangle(x0, y0, x1, y1, x2, y2, fillColor);
  tft.fillTriangle(x0, y0, x2, y2, x3, y3, fillColor); 
  tft.fillTriangle(x0, y0, x3, y3, x4, y4, fillColor);
  tft.fillTriangle(x0, y0, x4, y4, x5, y5, fillColor); 
  tft.drawLine(x0, y0, x1, y1, lineColor); tft.drawLine(x1, y1, x2, y2, lineColor); tft.drawLine(x2, y2, x3, y3, lineColor);
  tft.drawLine(x3, y3, x4, y4, lineColor); tft.drawLine(x4, y4, x5, y5, lineColor); tft.drawLine(x5, y5, x0, y0, lineColor);
  tft.drawLine(x0, y0, x7, y7, lineColor); tft.drawLine(x7, y7, x3, y3, lineColor); tft.drawLine(x3, y3, x6, y6, lineColor);
  tft.drawLine(x6, y6, x0, y0, lineColor); tft.drawLine(x8, y8, x6, y6, lineColor); tft.drawLine(x9, y9, x7, y7, lineColor);

  tft.setTextSize(sizeLabel);
  tft.setTextColor(fillColor == TFT_BLACK ? TFT_WHITE : TFT_BLACK);
  int text_w = tft.textWidth(label);
  tft.setCursor(cx - text_w / 2, cy - 8);
  tft.print(label);
  tft.setTextSize(2);
}

