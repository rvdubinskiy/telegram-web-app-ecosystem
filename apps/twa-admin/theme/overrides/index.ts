import type { Theme } from '@mui/material/styles';
import merge from 'lodash/merge';

import { Accordion } from './components/Accordion';
import { Alert } from './components/Alert';
import { AppBar } from './components/AppBar';
import { Autocomplete } from './components/Autocomplete';
import { Avatar } from './components/Avatar';
import { Backdrop } from './components/Backdrop';
import { Badge } from './components/Badge';
import { Breadcrumbs } from './components/Breadcrumbs';
import { Button } from './components/Button';
import { ButtonGroup } from './components/ButtonGroup';
import { Card } from './components/Card';
import { Checkbox } from './components/Checkbox';
import { Chip } from './components/Chip';
import { CssBaseline } from './components/CssBaseline';
import { DataGrid } from './components/DataGrid';
import { DatePicker } from './components/DatePicker';
import { Dialog } from './components/Dialog';
import { Drawer } from './components/Drawer';
import { Fab } from './components/Fab';
import { List } from './components/List';
import { LoadingButton } from './components/LoadingButton';
import { Menu } from './components/Menu';
import { Pagination } from './components/Pagination';
import { Paper } from './components/Paper';
import { Popover } from './components/Popover';
import { Progress } from './components/Progress';
import { Radio } from './components/Radio';
import { Rating } from './components/Rating';
import { Select } from './components/Select';
import { Skeleton } from './components/Skeleton';
import { Slider } from './components/Slider';
import { Stepper } from './components/Stepper';
import { SvgIcon } from './components/SvgIcon';
import { Switches } from './components/Switch';
import { Table } from './components/Table';
import { Tabs } from './components/Tabs';
import { TextField } from './components/TextField';
import { Timeline } from './components/Timeline';
import { ToggleButton } from './components/ToggleButton';
import { Tooltip } from './components/Tooltip';
import { TreeView } from './components/TreeView';
import { Typography } from './components/Typography';
import { defaultProps } from './defaultProps';

// ----------------------------------------------------------------------

export function componentsOverrides(theme: Theme) {
  const components = merge(
    defaultProps(theme),
    //
    Fab(theme),
    Tabs(theme),
    Chip(theme),
    Card(theme),
    Menu(theme),
    List(theme),
    Badge(theme),
    Table(theme),
    Paper(theme),
    Alert(theme),
    Radio(theme),
    Select(theme),
    Button(theme),
    Rating(theme),
    Dialog(theme),
    AppBar(theme),
    Avatar(theme),
    Slider(theme),
    Drawer(theme),
    Stepper(theme),
    Tooltip(theme),
    Popover(theme),
    SvgIcon(theme),
    Switches(theme),
    Checkbox(theme),
    DataGrid(theme),
    Skeleton(theme),
    Timeline(theme),
    TreeView(theme),
    Backdrop(theme),
    Progress(theme),
    TextField(theme),
    Accordion(theme),
    Typography(theme),
    Pagination(theme),
    DatePicker(theme),
    ButtonGroup(theme),
    Breadcrumbs(theme),
    CssBaseline(theme),
    Autocomplete(theme),
    ToggleButton(theme),
    LoadingButton(theme)
  );

  return components;
}
