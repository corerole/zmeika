module;

export module snake_logic;
import std;

export namespace snake_logic {

	struct Point2Di {
			using value_type = std::size_t;

		public:
			value_type x = 0;
			value_type y = 0;
	};

	enum class FieldObjects { FreeSpace, Wall, Apple, SnakeHead, SnakeTail };
	enum class Solutions { GameOver, TakeApple, Nothing };
	enum class GameCondition { Loose, Win, Process };

	struct GameField {
			using value_type = FieldObjects;
			using const_value_type = std::add_const_t<value_type>;
			using const_reference = std::add_lvalue_reference_t<const_value_type>;

		private:
			std::pmr::vector<std::pmr::vector<FieldObjects>> tiles;

		public:
			constexpr void set_tile(Point2Di p, FieldObjects obj) { tiles[p.y][p.x] = obj; }

		public:
			auto height() noexcept { return tiles.size(); }
			auto width() noexcept { return tiles[0].size(); }
			const_reference get_elem(Point2Di p) const noexcept { return tiles[p.y][p.x]; }

			// TODO :
			std::vector<Point2Di> find_elems(value_type type) {
				std::vector<Point2Di> res;
				res.reserve(height() * width());
				auto X = std::views::iota(0u, width());
				auto Y = std::views::iota(0u, height());
				for(auto y : Y) {
					for(auto x : X) {
						if(tiles[y][x] == type) {
							res.push_back({x, y});
						}
					}
				}
				res.shrink_to_fit();
				return res;
			}

		private:
			void set_borders() {
				auto h = height();
				auto w = width();
				auto x = std::views::iota(0u, w);
				auto y = std::views::iota(0u, h);

				for (auto i : x) {
					set_tile({i, 0u}, FieldObjects::Wall);
					set_tile({i, h - 1}, FieldObjects::Wall);
				}
				for (auto i : y) {
					set_tile({w - 1, i}, FieldObjects::Wall);
					set_tile({0u, i}, FieldObjects::Wall);
				}
			}

		public:
			void reset() {
				for(auto& line : tiles) {
					std::ranges::fill(line, FieldObjects::FreeSpace);
				}
				set_borders();
			}

			auto share() {
				using subrange_type = decltype(std::ranges::subrange(tiles[0].cbegin(), tiles[0].cend()));
				std::vector<subrange_type> vec;
				vec.reserve(tiles.size());
				for(auto& tile : tiles) {
					vec.push_back(subrange_type(tile.cbegin(), tile.cend()));
				}
				return vec;
			}

		public:
			GameField(std::size_t h, std::size_t w) {
				if (h < 4 || w < 4) { throw std::runtime_error("sdf"); }
				tiles.resize(h);
				for (auto& tile : tiles) {
					tile.assign(w, FieldObjects::FreeSpace);
				}
				set_borders();
			}
	};

	using void_ptr_t = void*;

	enum class Direction { UP, DOWN, LEFT, RIGHT };

	template <Direction D> constexpr Point2Di change_coord(Point2Di value) {
		if constexpr (D == Direction::UP) { return {value.x, --value.y}; }
		if constexpr (D == Direction::DOWN) { return {value.x, ++value.y}; }
		if constexpr (D == Direction::LEFT) { return {--value.x, value.y}; }
		if constexpr (D == Direction::RIGHT) { return {++value.x, value.y}; }
	}

	struct Snake {
			static constexpr Point2Di inital_pos = {2, 2};
			using value_type = std::pmr::list<std::pair<Point2Di, bool>>;
			using const_value_type = std::add_const_t<value_type>;
			using reference = std::add_lvalue_reference_t<value_type>;
			using const_reference = std::add_lvalue_reference_t<const_value_type>;

		private:
			value_type body;

		public:
			template <Direction D> std::pair<Point2Di, std::reference_wrapper<bool>> move() {
				body.insert(body.begin(), {change_coord<D>(body.front().first), false});
				if (!body.back().second) {
					body.pop_back();
				} else {
					body.back().second = false;
				}
				return {body.front().first, std::ref(body.front().second)};
			}

		public:
			auto get_draw_data() const { return std::ranges::subrange(body.cbegin(), body.cend()); }	// TODO
			void reset() { body.clear(); body.push_front({inital_pos, false}); }

		public:
			Snake()	: body() {
				body.push_front({inital_pos, false});
			}
	};

	struct RNG {
		private:
			std::random_device rd;

		public:
			std::size_t operator()(std::size_t upper_limit) {
				std::uniform_int_distribution<std::size_t> dist(0, upper_limit);
				return dist(rd);
			}
	};

	enum class Action { Unknown, MoveUp, MoveRight, MoveDown, MoveLeft, Quit };

	struct SnakeGame {
		private:
			GameField field;
			Snake snake;
			RNG rng;

		private:
			Solutions check_snake_move(std::pair<Point2Di, std::reference_wrapper<bool>> data) {
				auto tile_obj = field.get_elem(data.first);
				switch (tile_obj) {
					case FieldObjects::Apple: {
						data.second.get() = true;
						return Solutions::TakeApple;
						break;
					}
					case FieldObjects::SnakeTail:
					case FieldObjects::Wall: {
						return Solutions::GameOver;
						break;
					}
					default: {
						return Solutions::Nothing;
					}
				}
			}

			Solutions reaction(Action action) {
				switch (action) {
					case Action::Quit: { return Solutions::GameOver; }
					case Action::MoveUp: { return check_snake_move(snake.move<Direction::UP>()); }
					case Action::MoveDown: { return check_snake_move(snake.move<Direction::DOWN>()); }
					case Action::MoveLeft: { return check_snake_move(snake.move<Direction::LEFT>()); }
					case Action::MoveRight: {	return check_snake_move(snake.move<Direction::RIGHT>()); }
					case Action::Unknown: { return Solutions::Nothing;	}
					default: {	}
				}
				return Solutions::Nothing;
			};

			void add_snake_to_tiles() {
				auto w = field.width();
				auto h = field.height();
				auto X = std::views::iota(0u, w);
				auto Y = std::views::iota(0u, h);
				for (auto y : Y) {
					for (auto x : X) {
						auto tile_obj = field.get_elem({x, y});
						if (tile_obj == FieldObjects::SnakeHead || tile_obj == FieldObjects::SnakeTail) {
							field.set_tile({x, y}, FieldObjects::FreeSpace);
						}
					}
				}

				auto head = snake.get_draw_data().begin();
				field.set_tile(head->first, FieldObjects::SnakeHead);
				auto tail = std::ranges::subrange(std::next(snake.get_draw_data().begin()), snake.get_draw_data().end());
				for (auto&& pos : tail) {
					field.set_tile(pos.first, FieldObjects::SnakeTail);
				}
			};

		public:
			GameCondition game_iter(Action action) {
				auto solution = reaction(action);
				switch(solution) {
					case Solutions::GameOver: { 
						field.reset();
						snake.reset();
						return GameCondition::Loose;
					}
					case Solutions::TakeApple: {
						auto res = field.find_elems(FieldObjects::FreeSpace);
						if(res.size() == 0) {
							 return GameCondition::Win;
						} else {
							field.set_tile(res[rng(res.size())], FieldObjects::Apple);
						}
						break;
					}
					case Solutions::Nothing : {}
					default: {}
				}
				add_snake_to_tiles();
				return GameCondition::Process;
			}

		auto share() {
			return field.share();
		}

		public:
			SnakeGame(std::size_t height, std::size_t width)
				:	field(height, width)
				,	snake()
				, rng() {
					auto y = rng(height);
					auto x = rng(width);
					while( (x == 2 && y == 2) || (x < 2) || (x > width - 2) || (y < 2) || (y > height - 2) ) {
							y = rng(height);
							x = rng(width);
					}
					field.set_tile({x, y}, FieldObjects::Apple);
			}
	};

}	 // namespace snake_logic