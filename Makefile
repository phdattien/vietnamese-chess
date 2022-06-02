CXX= g++
CXXFLAGS = -std=c++17 -Wall -O3 -pedantic -Wextra -g -fsanitize=address
TARGET = phamtie2
BUILD_DIR = build
TEST_DIR = test
HEADERS = $(wildcard $(SOURCE_DIR)/game/*.h)

OBJ = $(BUILD_DIR)/main.o $(BUILD_DIR)/CAdvisor.o \
 $(BUILD_DIR)/CApplication.o \
 $(BUILD_DIR)/CBoard.o \
 $(BUILD_DIR)/CCannon.o \
 $(BUILD_DIR)/CChariot.o \
 $(BUILD_DIR)/CCoord.o \
 $(BUILD_DIR)/CElephant.o \
 $(BUILD_DIR)/CEvaluation.o \
 $(BUILD_DIR)/CFen.o \
 $(BUILD_DIR)/CGame.o \
 $(BUILD_DIR)/CGeneral.o \
 $(BUILD_DIR)/CHorse.o \
 $(BUILD_DIR)/CPawn.o \
 $(BUILD_DIR)/CPlayerHuman.o	\
 $(BUILD_DIR)/CPlayerRandomAI.o \
 $(BUILD_DIR)/CPlayerSmartAI.o \
 $(BUILD_DIR)/CSearch.o \
 $(BUILD_DIR)/Move.o \
 $(BUILD_DIR)/UI.o


all: compile doc

doc: Doxyfile README.md $(HEADERS)
	doxygen Doxyfile

run: $(TARGET)
	./$(TARGET)

compile: $(TARGET)


$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/main.o: src/main.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -c -o $@

$(BUILD_DIR)/%.o: src/game/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -c -o $@


# $(TEST_DIR)/test: tests/test.cpp tests/Perft.cpp src/game/CBoard.cpp
# 	$(CXX) $(CXXFLAGS) $^ -o $@

# runTest: $(TEST_DIR)/test
# 	./$(TEST_DIR)/test

clean:
	rm -rf $(TARGET) doc/ $(BUILD_DIR)/ 2>/dev/null


$(BUILD_DIR)/main.o: src/main.cpp src/game/CApplication.h src/game/CGame.h \
 src/game/CBoard.h src/game/CTroop.h src/game/CCoord.h \
 src/game/Constants.h src/game/Move.h src/game/CPlayer.h src/game/Draw.h
$(BUILD_DIR)/CAdvisor.o: src/game/CAdvisor.cpp src/game/CAdvisor.h src/game/CTroop.h \
 src/game/CCoord.h src/game/Constants.h
$(BUILD_DIR)/CApplication.o: src/game/CApplication.cpp src/game/CApplication.h \
 src/game/CGame.h src/game/CBoard.h src/game/CTroop.h src/game/CCoord.h \
 src/game/Constants.h src/game/Move.h src/game/CPlayer.h src/game/Draw.h \
 src/game/UI.h src/game/CQuitException.h
$(BUILD_DIR)/CBoard.o: src/game/CBoard.cpp src/game/CBoard.h src/game/CTroop.h \
 src/game/CCoord.h src/game/Constants.h src/game/Move.h src/game/CFen.h \
 src/game/CPositionInf.h
$(BUILD_DIR)/CCannon.o: src/game/CCannon.cpp src/game/CCannon.h src/game/CTroop.h \
 src/game/CCoord.h src/game/Constants.h
$(BUILD_DIR)/CChariot.o: src/game/CChariot.cpp src/game/CChariot.h src/game/CTroop.h \
 src/game/CCoord.h src/game/Constants.h
$(BUILD_DIR)/CCoord.o: src/game/CCoord.cpp src/game/CCoord.h
$(BUILD_DIR)/CElephant.o: src/game/CElephant.cpp src/game/CElephant.h \
 src/game/CTroop.h src/game/CCoord.h src/game/Constants.h
$(BUILD_DIR)/CEvaluation.o: src/game/CEvaluation.cpp src/game/CEvaluation.h \
 src/game/CBoard.h src/game/CTroop.h src/game/CCoord.h \
 src/game/Constants.h src/game/Move.h
$(BUILD_DIR)/CFen.o: src/game/CFen.cpp src/game/CFen.h src/game/CBoard.h \
 src/game/CTroop.h src/game/CCoord.h src/game/Constants.h src/game/Move.h \
 src/game/CPositionInf.h src/game/CAdvisor.h src/game/CCannon.h \
 src/game/CChariot.h src/game/CElephant.h src/game/CGeneral.h \
 src/game/CHorse.h src/game/CPawn.h
$(BUILD_DIR)/CGame.o: src/game/CGame.cpp src/game/CGame.h src/game/CBoard.h \
 src/game/CTroop.h src/game/CCoord.h src/game/Constants.h src/game/Move.h \
 src/game/CPlayer.h src/game/Draw.h src/game/CPlayerHuman.h \
 src/game/CPlayerRandomAI.h src/game/CPlayerSmartAI.h src/game/CSearch.h \
 src/game/CEvaluation.h src/game/UI.h
$(BUILD_DIR)/CGeneral.o: src/game/CGeneral.cpp src/game/CGeneral.h src/game/CTroop.h \
 src/game/CCoord.h src/game/Constants.h
$(BUILD_DIR)/CHorse.o: src/game/CHorse.cpp src/game/CHorse.h src/game/CTroop.h \
 src/game/CCoord.h src/game/Constants.h
$(BUILD_DIR)/CPawn.o: src/game/CPawn.cpp src/game/CPawn.h src/game/CTroop.h \
 src/game/CCoord.h src/game/Constants.h
$(BUILD_DIR)/CPlayerHuman.o: src/game/CPlayerHuman.cpp src/game/CPlayerHuman.h \
 src/game/CPlayer.h src/game/CBoard.h src/game/CTroop.h src/game/CCoord.h \
 src/game/Constants.h src/game/Move.h src/game/Draw.h src/game/UI.h \
 src/game/CFen.h src/game/CPositionInf.h src/game/CQuitException.h
$(BUILD_DIR)/CPlayerRandomAI.o: src/game/CPlayerRandomAI.cpp \
 src/game/CPlayerRandomAI.h src/game/CPlayer.h src/game/CBoard.h \
 src/game/CTroop.h src/game/CCoord.h src/game/Constants.h src/game/Move.h \
 src/game/Draw.h
$(BUILD_DIR)/CPlayerSmartAI.o: src/game/CPlayerSmartAI.cpp src/game/CPlayerSmartAI.h \
 src/game/CPlayer.h src/game/CBoard.h src/game/CTroop.h src/game/CCoord.h \
 src/game/Constants.h src/game/Move.h src/game/Draw.h src/game/CSearch.h \
 src/game/CEvaluation.h
$(BUILD_DIR)/CSearch.o: src/game/CSearch.cpp src/game/CSearch.h src/game/CBoard.h \
 src/game/CTroop.h src/game/CCoord.h src/game/Constants.h src/game/Move.h \
 src/game/CEvaluation.h
$(BUILD_DIR)/Move.o: src/game/Move.cpp src/game/Move.h src/game/CCoord.h
$(BUILD_DIR)/UI.o: src/game/UI.cpp src/game/UI.h src/game/CBoard.h src/game/CTroop.h \
 src/game/CCoord.h src/game/Constants.h src/game/Move.h

# $(TEST_DIR)/CPerft.o: tests/Perft.cpp tests/Perft.h  src/game/CBoard.h
# $(TEST_DIR)/test.o: tests/test.cpp tests/Perft.h  src/game/CBoard.h
