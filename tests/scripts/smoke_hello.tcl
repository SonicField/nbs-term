# tests/scripts/smoke_hello.tcl — minimal harness self-test
#
# Smoke verification for tests/test_render_state.phc. Feeds 5 ASCII bytes,
# renders, asserts the harness comes back through nbs_test_complete.
# Validates the round-trip: vt_parser ingest + render_screen synchronous
# call + canvas item generation + golden compare. NOT a per-surface test
# in its own right — those are added per generalist's items 5-10.

nbs_test_feed_bytes "hello"
nbs_test_render
nbs_test_complete
